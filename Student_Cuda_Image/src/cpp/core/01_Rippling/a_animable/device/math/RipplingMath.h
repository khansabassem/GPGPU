#pragma once

#include <math.h>
#include "Maths.h"

#include "Colors_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class RipplingMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	__device__ RipplingMath(uint w , uint h,float t) :
		dim2(w / 2),//
		t(t)
	    {
	    // rien
	    }

	__device__
	      virtual ~RipplingMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorIJ(uchar4* ptrColorIJ , int i , int j )
	    {
	    uchar levelGris;

	    levelGray(i,j, &levelGris); // update levelGris

	    ptrColorIJ->x = levelGris;
	    ptrColorIJ->y = levelGris;
	    ptrColorIJ->z = levelGris;

	    ptrColorIJ->w = 255; //opaque

	    // Conseil:
	    // 		Etape 1 : 	Commencer par afficher une image uniforme grise (128 par exemple)
	    // 				pour valider tout le pipeline en amont
	    //
	    // 		Etape 2:	Puis une fois que l'image grise est valider, attaquer rippling
	    }

    private:

	__inline__
	__device__
	void levelGray(int i , int j ,  uchar* ptrLevelGray)
	    {
	    float result;
	    dij(i, j, &result); // warning : dij return void. Ne peut pas etre "imbriquer dans une fonction"
	    result = result / 10.f;
	    const float cs = cosf(result - t/7) /(result + 1);
	    *ptrLevelGray = 128 + 127*cs;
	    }

	__inline__
	__device__
	void dij(int i , int j , float* ptrResult)
	    {
	    float fi = i - this->dim2;
	    float fj = j - this->dim2;
	    *ptrResult = sqrtf(fi*fi + fj*fj);
	    }

	/*--------------------------------------*\
	|*		Attribut			*|
	 \*-------------------------------------*/

    private:

	// Tools
	int dim2;	    // dim2=dim/2
	float t;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
