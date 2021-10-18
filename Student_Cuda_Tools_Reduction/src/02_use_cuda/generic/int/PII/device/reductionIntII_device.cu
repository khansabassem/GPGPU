#include "Thread1D.h"
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

static __device__ void reductionIntraThread(int* tabSM);

// Operateur reduction
static __device__ int add(int x , int y);
static __device__ void addAtomicV1(int* ptrX , int y);
static __device__ void addAtomicV2(int* ptrX , int y);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void KIntProtocoleII(int* ptrSumGM)
    {
    extern __shared__ int tabSM[];
    reductionIntraThread (tabSM);
    __syncthreads();

    Reduction::reduce(add, addAtomicV1, tabSM, ptrSumGM);
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

/*----------------------------*\
|*	Operateur reduction    *|
 \*---------------------------*/

__device__ int add(int x , int y)
    {
    return x + y;
    }

/**
 * Utiliser la methode system : atomicAdd(pointeurDestination, valeurSource);
 */
__device__ void addAtomicV1(int* ptrX , int y)
    {
    atomicAdd(ptrX, y);
    }

/**
 * Une alternative, moins performante, mais generalisable serait d'employer un lock
 * Tip : le Lock est implementer avec deux methodes atomic
 */
__device__ int volatile mutex = 0;	//variable global
__device__ void addAtomicV2(int* ptrX , int y)
    {
    Lock locker(&mutex);
    locker.lock();

    (*ptrX) += y;

    locker.unlock();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

