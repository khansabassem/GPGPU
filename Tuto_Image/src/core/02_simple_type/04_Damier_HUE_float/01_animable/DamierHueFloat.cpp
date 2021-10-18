#include "DamierHueFloat.h"
#include "DamierHueFloatMath.h"

#include <iostream>
#include <omp.h>
#include "Omps.h"

#include "Indices_CPU.h"
using cpu::Indices;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

DamierHueFloat::DamierHueFloat(uint w , uint h , float dt , uint n , const DomaineMath& domaineMath) :
	Animable_I<float>(w, h, "Damier_OMP_hue_float", domaineMath), //
	variateurAnimation(Interval<float>(0, 2 * PI), dt),//
	n(n)
    {
    // Tools
    this->t = 0;					// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[Damier] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

DamierHueFloat::~DamierHueFloat(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void DamierHueFloat::animationStep()
    {
    this->t = variateurAnimation.varierAndGet(); // in [0,2pi]
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 */
void DamierHueFloat::processForAutoOMP(float* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    DamierHueFloatMath damierMath(n); // ici pour preparer cuda

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    // int s = i * W + j;
	    int s = Indices::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	    workPixel(&tabPixels[s], i, j, domaineMath, &damierMath);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 */
void DamierHueFloat::processEntrelacementOMP(float* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    DamierHueFloatMath damierMath(n); // ici pour preparer cuda

    const int WH = w * h;

#pragma omp parallel
	{
	const int NB_THREAD = Omps::getNbThread(); // dans region parallel
	const int TID = Omps::getTid();

	int i;
	int j;

	int s = TID; // in [0,...
	while (s < WH)
	    {
	    Indices::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    workPixel(&tabPixels[s], i, j, domaineMath, &damierMath);

	    s += NB_THREAD;
	    }
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * i in [0,h[
 * j in [0,w[
 *
 * code commun a:
 * 	- entrelacementOMP
 * 	- forAutoOMP
 */
void DamierHueFloat::workPixel(float* ptrColorIJ , int i , int j , const DomaineMath& domaineMath , DamierHueFloatMath* ptrDamierMath)
    {
    // (i,j) domaine ecran dans N2
    // (x,y) domaine math dans R2

    double x;
    double y;
    domaineMath.toXY(i, j, &x, &y); // fill (x,y) from (i,j)

    // float t=variateurAnimation.get();

    ptrDamierMath->colorXY(ptrColorIJ, x, y, t); // in [01]
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

