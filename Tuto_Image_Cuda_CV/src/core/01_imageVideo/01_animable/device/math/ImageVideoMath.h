#pragma once

#include <math.h>
#include "Maths.h"

#include "Colors_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class ImageVideoMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ ImageVideoMath(int w , int h) :
		POIDS(1 / (double)3)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	__device__
	     virtual ~ImageVideoMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColor , int i , int j , float t)
	    {
	    uchar r = ptrColor->x;
	    uchar g = ptrColor->y;
	    uchar b = ptrColor->z;

	    uchar levelGris = r * POIDS + g * POIDS + b * POIDS;

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Tools
	float POIDS;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
