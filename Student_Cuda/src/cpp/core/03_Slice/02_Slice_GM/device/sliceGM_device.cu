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
 * puis stocke son résultat dans SA case dans tabGM
 *
 * tabGM est un tableau promu, qui a autant de case que de thread
 * </pre>
 */
__global__ void reductionIntraThreadGM(float* tabGM , int nbSlice)
    {
    const int NB_THREAD = Thread1D::nbThread();
    const int TID = Thread1D::tid();
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

/**
 * <pre>
 * Effectue la reduction de tabGM cote device, par ecrasement 2 à 2 successif.
 * Ce kernel d ecrasement est appeler depuis le host dans une boucle, avec le bon nombre de thread
 *
 * Hypothese : |tabGM| est une puissance de 2
 *
 * Output: le resultat de la reduction est tans tabGM[0]
 * </pre>
 */
__global__ void ecrasementGM(float* tabGM , int middle)
    {
    const int TID = Thread1D::tid();
    tabGM[TID] += tabGM[TID + middle];
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

