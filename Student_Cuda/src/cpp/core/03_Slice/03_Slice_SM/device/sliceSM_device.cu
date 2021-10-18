#include "Thread2D.h"
#include "Thread1D.h"
#include "ReductionAdd.h"

#include "cudas.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(float* tabSM,int nbSlice);
static __device__ float f(float x);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void sliceSM(int nbSlice , float* ptrPiHatGM)
    {
    // Declarer tabSM
    extern __shared__ float tabSM[];

    // ReductionIntraThread
    reductionIntraThread(tabSM, nbSlice);

    __syncthreads();

    // Reduction de tabSM (use tools ReductionAdd)
    ReductionAdd::reduce(tabSM, ptrPiHatGM); // T* tabSM, T* ptrResultGM

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * remplit la sm
 */
void reductionIntraThread(float* tabSM , int nbSlice)
    {
    const int TID = Thread1D::tid();
    const int TID_LOCAL = Thread1D::tidLocal();
    const int NB_THREAD = Thread1D::nbThread(); // DIFF entre nbthreadblock et nbthreadlocal ?
    int s = TID;

    const float DX = 1 / (float)nbSlice;
    float threadSum = 0;
    float xi;

    while (s < nbSlice)
	{
	xi = s * DX; // x value of function
	threadSum += f(xi);
	s += NB_THREAD;
	}
    tabSM[TID_LOCAL] = threadSum * DX;
    }

__device__ float f(float x)
    {
    return 4 / (1 + (x * x));
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

