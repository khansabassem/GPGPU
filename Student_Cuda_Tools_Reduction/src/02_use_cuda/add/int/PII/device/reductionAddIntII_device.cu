#include "Thread1D.h"
#include "cudas.h"

#include "ReductionAdd.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(int* tabSM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void KAddIntProtocoleII(int* ptrSumGM)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread (tabSM);
    __syncthreads();
    ReductionAdd::reduce(tabSM, ptrSumGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * TID partout en tabSM
 */
__device__ void reductionIntraThread(int* tabSM)
    {
    const int TID = Thread1D::tid();
    tabSM[threadIdx.x] = TID; // global pour le PII
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

