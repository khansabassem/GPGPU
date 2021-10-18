#include "Thread2D.h"
#include "Thread1D.h"
#include "cudas.h"

#include "Indices_GPU.h"

#include "RipplingMath.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void rippling(uchar4* tabPixelsGM , uint w , uint h , float t)
    {
    RipplingMath ripplingMath = RipplingMath(w , h, t);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;
    int pixelI, pixelJ;
    int s = TID;
    while(s<WH){

	Indices::toIJ(s, w, &pixelI, &pixelJ);

	ripplingMath.colorIJ(&tabPixelsGM[s], pixelI, pixelJ);

	s+= NB_THREAD;
        }
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

