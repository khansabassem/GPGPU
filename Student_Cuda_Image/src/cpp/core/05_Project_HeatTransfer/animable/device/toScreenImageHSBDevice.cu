#include <iostream>
#include "Thread2D.h"
#include "cudas.h"
#include "Indices_GPU.h"
#include "Interval_GPU.h"
#include "Calibreur_GPU.h"
#include "Colors_GPU.h"
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

__global__ void heatTransferToScreenImageHSB(uchar4* ptrDevPixels , real* ptrImageInput , int w , int h);

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

__global__ void heatTransferToScreenImageHSB(uchar4* ptrDevPixels , real* ptrImageInput , int w , int h)
    {
    const int WH = w * h;

    const int NB_THREAD = Thread2D::nbThread();
    const int TID = Thread2D::tid();

    int s = TID;

    real heatMax = 1.0;
    real heatMin = -0.2;
    real hueMax = 0;
    real hueMin = 0.66;

    real pente = (hueMax - hueMin) / (heatMax - heatMin);
    real translation = hueMin - pente * heatMin;
    while (s < WH)
	{
	float hue = ptrImageInput[s] * pente + translation;
	uchar4 p;
	gpu::Colors::HSB_TO_RVB(hue, 1, 1, &p.x, &p.y, &p.z);
	ptrDevPixels[s] = p;
	s += NB_THREAD;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
