#include "cuda_runtime.h"
#include "Newton.h"
#include <iostream>
#include <assert.h>
#include "Maths.h"
#include "Hardware.h"
/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void newton(uchar4* tabPixelsGM, uint w, uint h, DomaineMath domaineMath, uint n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Newton::Newton(const Grid& grid , uint w , uint h , uint nMin, uint nMax, const DomaineMath& domaineMath) :
	Animable_I<uchar4>(grid, w, h, "Newton_Cuda_RGBA_uchar4", domaineMath),
	variateurN(Interval<int>(nMin, nMax), 1) //
//	variateurN(Interval<int>(10,1000),1)
//	n(n)

    {

    // Inputs
    this->w = w;
    this->h = h;
//    this->ptrDomaineMathInit = domaineMath;

    // get dg, db
    this->dg = grid.dg;
    this->db= grid.db;

    // Tools
    //Outputs
    this->title = "Newton_CUDA (Zoomable)";
    }

Newton::~Newton()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 */
void Newton::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    //time elapsed for kernel calls, perf indicator
    newton<<<dg,db>>>(tabPixelsGM,w,h,domaineMath,n);
    // newton<<<w,h>>>(tabPixelsGM,w,h,domaineMath,n);
//    newton<<<Hardware::getMPCount(),Hardware::getCoreCountMP()*16>>>(tabPixelsGM,w,h,domaineMath,n);
//    cudaThreadSynchronize();
//    clock_t end = clock();
//    printf("n=%d    Time Elapsed: %.3lf ms\n", n, (double)(end-begin)/CLOCKS_PER_SEC*1000.0);
    //printf("n=%d    Time Elapsed: %.3lf ms\n", n, (double)(end-begin)/CLOCKS_PER_SEC*1000.0);
    }

/**
 * Override
 * Call periodicly by the API
 */
void Newton::animationStep()
{
this->n = variateurN.varierAndGet()/10; // in [0,2pi]
}


/*--------------*\
 |*	get	 *|
 \*--------------*/

/**
 * Override
 */
//DomaineMath* Newton::getDomaineMathInit(void)
//{
//return ptrDomaineMathInit;
//}

/**
 * Override
 */
float Newton::getAnimationPara(void)
{
return n;
}

/**
 * Override
 */
int Newton::getW(void)
{
return w;
}

/**
 * Override
 */
int Newton::getH(void)
{
return h;
}

/**
 * Override
 */
string Newton::getTitle(void)
{
return title;
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

