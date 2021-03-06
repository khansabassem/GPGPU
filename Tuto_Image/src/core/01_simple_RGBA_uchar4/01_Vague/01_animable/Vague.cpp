#include "Vague.h"
#include "VagueMath.h"

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

Vague::Vague(uint w , uint h , int dt) :
	Animable_I<uchar4>(w, h, "Vague_OMP_rgba_uchar4")
    {
    // Input
    this->dt = dt;

    // Tools
    this->t = 0;			// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[VAGUE] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

Vague::~Vague(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Vague::animationStep()
    {
    t += dt;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Override (code naturel omp)
 * Image non zoomable : domaineMath pas use ici
 */
void Vague::processForAutoOMP(uchar4* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    VagueMath vagueMath(w, h); // ici pour preparer cuda

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    // int s = i * W + j;
	    int s = Indices::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	    vagueMath.colorIJ(&tabPixels[s], i, j, t);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 * Image non zoomable : domaineMath pas use ici
 */
void Vague::processEntrelacementOMP(uchar4* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    VagueMath vagueMath(w, h); // ici pour preparer cuda

    const int WH = w * h;

    const int NB_THREAD = Omps::setAndGetNaturalGranularity();

#pragma omp parallel
	{
	const int TID = Omps::getTid();
	//const int NB_THREAD = Omps::getNbThread(); // dans region parallel

	int i;	// in [0,h[
	int j; 	// in [0,w[

	int s = TID; // in [0,...
	while (s < WH)
	    {
	    Indices::toIJ(s, w, &i, &j); // s[0,W*H[ --> i[0,H[ j[0,W[

	    vagueMath.colorIJ(&tabPixels[s], i, j, t); // update ptrTabPixels[s]

	    s += NB_THREAD;
	    }
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

