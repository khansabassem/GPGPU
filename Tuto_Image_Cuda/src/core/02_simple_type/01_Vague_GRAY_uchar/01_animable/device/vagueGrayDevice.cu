#include "Thread2D.h"
#include "cudas.h"
#include "VagueGrayMath.h"

#include "Indices_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void vagueGray(uchar* tabPixelsGM , uint w , uint h , int t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void vagueGray(uchar* tabPixelsGM , uint w , uint h , int t)
    {
    VagueGrayMath vagueGrayMath(w, h,t);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;

    int i; // in [0,h[
    int j; // in [0,w[

    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &i, &j); 	// update (i, j)

	vagueGrayMath.colorIJ(&tabPixelsGM[s], i, j); 	// update ptrDevPixels[s]

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

