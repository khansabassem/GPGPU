#include <stdio.h>
#include <curand_kernel.h>

#include "Thread1D.h"
#include "cudas.h"
#include "entier.h"
#include "Lock.h"
#include "ReductionAdd.h"
#include "Reduction.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ static void reductionIntraThread(curandState* tabGeneratorGM , entier* tabSM , entier nbDarByThread , float h);
__device__ static float f(float x);

__device__ static long add(long x , long y);
__device__ static void addAtomic(long* ptrX , long y);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*-------------------*\
|* generateur alea   *|
 \*------------------*/

/**
 * Each thread gets same seed, a different sequence number, no offset
 * host side : Device::getDeviceId();
 */
__global__ void createGenerator(curandState* tabGeneratorGM , int deviceId)
    {
    // Customisation du generator:
    // Proposition, au lecteur de faire mieux !
    // Contrainte : Doit etre différent d'un GPU à l'autre
    // Contrainte : Doit etre différent d'un thread à l'autre

    const int TID = Thread1D::tid();
    int deltaSeed = deviceId * INT_MAX / 10000;
    int deltaSequence = deviceId * 100;
    int deltaOffset = deviceId * 100;
    int seed = 1234 + deltaSeed;
    int sequenceNumber = TID + deltaSequence;
    int offset = deltaOffset;

    curand_init(seed, sequenceNumber, offset, &tabGeneratorGM[TID]);
    }

/*-------------------*\
|* reduce 	     *|
 \*------------------*/

/**
 *
 * Chaque thread doit
 * 		1) tirer nbDarByThread et compter le nombre de dar sous la courbe
 * 		2) Le ranger sans sa case en tabSM
 * Puis on reduit les tabSM
 */
__global__ void montecarlo(curandState* tabGeneratorGM , entier nbDarByThread , entier* ptrNbDarUnderGM , float h)
    {
    // TODO Montecarlo
    extern __shared__ entier tabSM[];
    reductionIntraThread(tabGeneratorGM, tabSM, nbDarByThread, h);
    __syncthreads();

    // reduction des tabSM
	{
#ifdef DAR_INT
	ReductionAdd::reduce(tabSM, ptrNbDarUnderGM);
#endif

#ifdef DAR_LONG
	Reduction::reduce(add, addAtomic, tabSM, ptrNbDarUnderGM);
#endif
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__
void reductionIntraThread(curandState* tabGeneratorGM , entier* tabSM , entier nbDarByThread , float h)
    {
    const int TID = Thread1D::tid();
    const int TID_LOCAL = Thread1D::tidLocal();

    // Global Memory -> Register (optimization)
    curandState generatorThread = tabGeneratorGM[TID];

    entier nbDarUnderCurveThread = 0;

    float xAlea01;
    float yAlea0h;

    for (entier i = 1; i <= nbDarByThread; ++i)
	{
	xAlea01 = curand_uniform(&generatorThread); // in [0,1[
	yAlea0h = curand_uniform(&generatorThread) * h; // in [0,h[
	float thrownY = f(xAlea01);
	if (thrownY > yAlea0h)
	    {
	    nbDarUnderCurveThread++;
	    }

	}

    // stocker resultat du thread dans tabSM
    tabSM[TID_LOCAL] = nbDarUnderCurveThread;

    //Register -> Global Memory
    //Necessaire si on veut utiliser notre generator
    //	- dans d'autre kernel
    //	- avec d'autres nombres aleatoires !
    tabGeneratorGM[TID] = generatorThread;
    }

__device__ float f(float x)
    {
    return 4.f / (1.f + x * x);
    }

/*-------------------*\
|* reduce operator   *|
 \*------------------*/

__device__ long add(long x , long y)
    {
    return x + y;
    }

/**
 * Utiliser la methode system : atomicAdd(pointeurDestination, valeurSource)
 * ou la technique du lock si atomicAdd existe pas pour les long
 */
__device__ int volatile mutex = 0;	//variable global
__device__ void addAtomic(long* ptrX , long y)
    {
    Lock locker(&mutex);
    locker.lock();
    *ptrX += y;
    locker.unlock();
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

