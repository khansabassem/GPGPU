#include <iostream>
#include "Thread2D.h"
#include "cudas.h"
#include "Indices_GPU.h"

using std::cout;
using std::endl;

#include "heatReal.h"


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void diffusion(real* ptrImageInput , real* ptrImageOutput , int w , int h);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__device__ real D_operator(real* ptrImage , int s , int w , int cardinalCoefficientNS , int cardinalCoefficientWE)
    {
    const real k = 0.21;
    const real adjustedWindNorth = ((real)1 + ((real)cardinalCoefficientNS / (real)100));
    const real adjustedWindEAST = ((real)1 + ((real)cardinalCoefficientWE / (real)100.0));

    const real south = ptrImage[s + w] * adjustedWindNorth;
    const real north = ptrImage[s - w] / adjustedWindNorth;
    const real east = ptrImage[s + 1] / adjustedWindEAST;
    const real west = ptrImage[s - 1] * adjustedWindEAST;
    const real quadri = 4;

    return ptrImage[s] + k * (south + north + east + west - quadri * ptrImage[s]);
    }

__global__ void heatTransferDiffusion(real* ptrImageInput , real* ptrImageOutput , int w , int h , int cardinalCoefficientNS , int cardinalCoefficientWE)
    {
    const int WH = w * h;

    const int NB_THREAD = Thread2D::nbThread();
    const int TID = Thread2D::tid();

    int s = TID;

    while (s < WH)
	{
	// on n'applique pas la diffusion sur les bords
	if (s > w && s < WH - w && (w - 1) % s != 0 && w % s != 0)
	    ptrImageOutput[s] = D_operator(ptrImageInput, s, w, cardinalCoefficientNS, cardinalCoefficientWE);

	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
