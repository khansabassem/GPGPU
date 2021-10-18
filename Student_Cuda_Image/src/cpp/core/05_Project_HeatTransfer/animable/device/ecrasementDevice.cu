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

__global__ void heatTransferEcrasement(real* ptrImageInOutput , int w , int h);

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

__global__ void heatTransferEcrasement(real* ptrImageInOutput , real* ptrImageHeater , int w , int h)
    {
    const int WH = w * h;

    const int NB_THREAD = Thread2D::nbThread();
    const int TID = Thread2D::tid();

    int s = TID;

    while (s < WH)
	{
	if (ptrImageHeater[s] != (real)0)
	    ptrImageInOutput[s] = ptrImageHeater[s];
	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
