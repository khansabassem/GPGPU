#include <assert.h>

#include "Thread2D.h"
#include "cudas.h"
#include "Indices_GPU.h"

#include "Sphere.h"
#include "nbSphere.h"
#include "SM.h"
#include "raytracingCM.h"
#include "RaytracingMath.h"
#include "DomaineMath_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static __device__ void work(uchar4* tabPixelsGM, uint w, uint h, float t, Sphere* tabSpheresDev, int nbSpheres);
static __device__ void copyDevToSM(Sphere* ptrSpheresGM , Sphere* ptrSpheresSM , int size);
/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void kernelRaytacingGM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres)
    {
    // TODO Raytracing GPU GM

    // Indications :
    //		(I1) Call methode work with good input
    // 		(I2) work contain the algo
    //		(I3) The algo is the same with the GM,CM,SM of TP Ractracing
    work(tabPixelsGM, w, h, t, tabSpheresGM, nbSpheres);

    }

__global__ void kernelRaytacingSM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres)
    {
    // TODO Raytracing GPU SM

    // Indications :
    //		(I1) Copier les sphere de GM to SM
    // 		(I2) Call work with good input
    //		(I3) Implementer une methode copyGMtoSM
    extern __shared__ Sphere tabSpheresSM[];
    copyDevToSM(tabSpheresGM, tabSpheresSM, nbSpheres);
    __syncthreads();
    work(tabPixelsGM, w, h, t, tabSpheresSM, nbSpheres);
    }

__device__ void copyDevToSM(Sphere* ptrSpheresGM , Sphere* ptrSpheresSM , int size)
    {
    const int TID_LOCAL = Thread2D::tidLocal();
    const int NB_THREAD_BLOCK = Thread2D::nbThreadBlock();
    int s = TID_LOCAL;
    while (s < size)
	{
	ptrSpheresSM[s] = ptrSpheresGM[s];
	s += NB_THREAD_BLOCK;
	}
    }

__global__ void kernelRaytacingCM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres)
    {
    work(tabPixelsGM, w, h, t, TAB_SPHERES_CM, nbSpheres);
    // Indications :
    //		(I1) call work with good input
    // 		(I2) TAB_SPHERES_CM est une variable globale a ce fichier! (Voir le debut de ce fichier, include rayTracingCM.h)
    }

__global__ void kernelRaytacingCM2SM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres)
    {
    // TODO Raytracing GPU SM_BY_CM
    extern __shared__ Sphere tabSpheresSM[];
    copyDevToSM(TAB_SPHERES_CM , tabSpheresSM , nbSpheres);
    __syncthreads();
    work(tabPixelsGM, w, h, t, tabSpheresSM, nbSpheres);
    // Indications :
    //		(I1) Copier les sphere de CM to SM
    // 		(I2) Call work with good input
    //		(I3) Implementer une methode copyCMtoSM
    //		     ou : Tip : renommer copyGMtoSM en copyDevToSM et utiliser copyDevToSM avec les bons inputs
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

/**
 * Methode commune au 3 kernel ci-dessus.
 * Ici on ne sait pas si derriere tabSpheresDev, c'est
 * 	- de la GM?
 * 	- de la SM?
 * 	- de la CM?
 * Pas d'importance, c'est un pointeur et on travail avec!
 */
__device__ void work(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresDev , int nbSpheres)
    {
    RaytracingMath raytracingMath(tabSpheresDev, nbSpheres, t);
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;
    int pixelI, pixelJ;
    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &pixelI, &pixelJ);
	raytracingMath.colorXY(&tabPixelsGM[s], pixelI, pixelJ);
	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

