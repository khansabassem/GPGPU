#include "Thread2D.h"
#include "Thread1D.h"
#include "cudas.h"

#include <stdio.h>

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * output : void required !!
 * pattern entrelacement
 */
// ptrDev pointeur device, 2 espaces mémoire différents => ne pas les mélanger
__global__ void addVector(float* ptrDevV1 , float* ptrDevV2 , float* ptrDevW , int n)
    {
    const int NB_THREAD = Thread2D::nbThread();
    const int TID = Thread2D::tid();
    int s = TID;
    while (s < n)
	{
	ptrDevW[s] = ptrDevV1[s] + ptrDevV2[s];
	s += NB_THREAD;
	}

    //TODO AddVector pattern entrelacement
    }

/**
 * pattern 1<-->1
 * hyp: #thread=#caseVecteur=n => 10 case en 10 thread
 */
__global__ void addVector11(float* ptrDevV1 , float* ptrDevV2 , float* ptrDevW , int n)
    {
    const int TID = Thread2D::tid();
    ptrDevW[TID] = ptrDevV1[TID] + ptrDevV2[TID];
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

