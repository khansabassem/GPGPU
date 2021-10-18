#include "Thread2D.h"
#include "cudas.h"

#include "ImageVideoMath.h"

#include "Indices_GPU.h"
using namespace gpu;

// Attention : 	Choix du nom est impotant!
//		VagueDevice.cu et non Vague.cu
// 		Dans ce dernier cas, probl�me de linkage, car le nom du .cu est le meme que le nom d'un .cpp (host)
//		On a donc ajouter Device (ou n'importequoi) pour que les noms soient diff�rents!

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void toGray(uchar4* tabPixelsGM , uint w , uint h , float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void toGray(uchar4* tabPixelsGM , uint w , uint h , float t)
    {
    ImageVideoMath math(w, h);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    int pixelI;	// in [0,h[
    int pixelJ; // in [0,w[

    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &pixelI, &pixelJ); 	// update (pixelI, pixelJ)

	math.colorIJ(&tabPixelsGM[s], pixelI, pixelJ, t); 	//update color  // ici pas besoin de i, j,t, optimisation possible

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

