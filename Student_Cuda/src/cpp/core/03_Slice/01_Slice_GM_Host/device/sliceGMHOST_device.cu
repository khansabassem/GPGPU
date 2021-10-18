#include "Thread2D.h"
#include "Thread1D.h"
#include "cudas.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * <pre>
 * Chaque thread effecteur une reduction intrathread avec le patern d'entrelacement,
 * puis stocke son resultat dans SA case dans tabGM
 *
 * tabGM est un tableau promu, qui a autant de case que de thread
 * </pre>
 */
__global__ void reductionIntraThreadGMHOST(float* tabGM , int nbSlice) // grid 1d
    {
    const int NB_THREAD = Thread2D::nbThread();
    const int TID = Thread2D::tid();
    float threadSum = 0;
    int s = TID;
    const float DX = 1 / (float)nbSlice;
    float xi;
    while (s < nbSlice)
	{
	xi = s * DX; // x value of function
	threadSum += f(xi);
	s += NB_THREAD;
	}
    tabGM[TID] = threadSum;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ float f(float x)
    {
    return 4 / (1 + (x * x));
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

