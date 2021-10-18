#include <iostream>
#include <omp.h>
#include "Omps.h"

#include "Indices_CPU.h"

#include "VagueGrayMath.h"
#include "VagueGray.h"
using cpu::Indices;

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

VagueGray::VagueGray(uint w , uint h , int dt) :
	Animable_I<uchar>(w, h, "Vague_OMP_gray_uchar"),//
	dt(dt)
    {
    // Tools
    this->t = 0;			// protected dans super classe Animable
    this->parallelPatern = ParallelPatern::OMP_MIXTE;   // protected dans super classe Animable

    // OMP
    cout << "\n[VAGUE] : OMP : nbThread = " << this->nbThread << endl; // protected dans super classe Animable
    }

VagueGray::~VagueGray(void)
    {
    // rien
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
void VagueGray::animationStep()
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
void VagueGray::processForAutoOMP(uchar* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    VagueGrayMath vagueGrayMath(w, h); // ici pour preparer cuda

#pragma omp parallel for
    for (int i = 0; i < h; i++)
	{
	for (int j = 0; j < w; j++)
	    {
	    // int s = i * W + j;
	    int s = Indices::toS(w, i, j);    // i[0,H[ j[0,W[  --> s[0,W*H[

	    vagueGrayMath.colorIJ(&tabPixels[s], i, j, t);
	    }
	}
    }

/**
 * Override (code entrainement cuda)
 * Image non zoomable : domaineMath pas use ici
 */
void VagueGray::processEntrelacementOMP(uchar* tabPixels , uint w , uint h , const DomaineMath& domaineMath)
    {
    VagueGrayMath vagueGrayMath(w, h); // ici pour preparer cuda

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

	    vagueGrayMath.colorIJ(&tabPixels[s], i, j, t);

	    s += NB_THREAD;
	    }
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

