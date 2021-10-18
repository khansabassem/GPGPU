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

__global__ void KAddIntProtocoleI(int* ptrSumGM)
    {
    // TODO ReductionAddIntI

    // Declaration tabSM
    // ReductionIntraThread
    // ReductionAdd
    extern __shared__ int tabSM[];
    reductionIntraThread (tabSM);
    __syncthreads();
    ReductionAdd::reduce(tabSM, ptrSumGM);
    //syncthreads implicite
    // __syncthreads(); // des threads de meme block!// Question : utile? ou?
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * 1 partout en tabSM
 */
__device__ void reductionIntraThread(int* tabSM)
    {
    const int TID_LOCAL = Thread1D::tidLocal();
    tabSM[TID_LOCAL] = 1; // global pour le PII

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

