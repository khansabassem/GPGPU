#include "Thread1D_long.h"
#include "cudas.h"

#include "Reduction.h"
#include "Lock.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void reductionIntraThread(long* tabSM);

// Operateur reduction
static __device__ long add(long x , long y);
static __device__ void addAtomic(long* ptrX , long y);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * TID partout en tabSM
 */
__global__ void KLongProtocoleII(long* ptrSumGM)
    {
    extern __shared__ long tabSM[];
    reductionIntraThread (tabSM);
    __syncthreads();

    Reduction::reduce(add, addAtomic, tabSM, ptrSumGM);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * TID partout en tabSM
 */
__device__ void reductionIntraThread(long* tabSM)
    {
    //		Juste (v1):	const long TID=((long)blockDim.x * (long) blockIdx.x)+ (long)threadIdx.x;
    //
    //		Juste (V2):	const long TID=Thread1D_long::tid();
    //
    //		Juste (V3):	const long TID=Thread2D_long::tid();
    const long TID = Thread1D_long::tid();
    tabSM[threadIdx.x] = TID; // global pour le PII
    }

/*----------------------------*\
|*	Operateur reduction    *|
 \*---------------------------*/

__device__ long add(long x , long y)
    {
    return x + y;
    }

/**
 * Utiliser la methode system, si elle existe
 *
 * 	atomicAdd(pointeurDestination, valeurSource)
 *
 * ou la technique du lock vu precedement!
 *
 * Question : atomicAdd pour les long existe?
 */
__device__ int volatile mutex = 0;	//variable global
__device__ void addAtomic(long* ptrX , long y)
    {
    Lock locker(&mutex);
    locker.lock();

    (*ptrX) += y;

    locker.unlock();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

