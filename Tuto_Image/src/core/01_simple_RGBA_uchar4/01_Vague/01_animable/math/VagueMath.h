#pragma once

#include <math.h>
#include "Maths.h"

#include "cudaType_CPU.h"
#include "Colors_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * Dans un header only pour preparer la version cuda
 */
class VagueMath
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	VagueMath(int w , int h) :
		h(h)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	virtual ~VagueMath(void)
	    {
	    //rien
	    }

	/*--------------------------------------*\
	 |*		Methode			*|
	 \*-------------------------------------*/

    public:

	/**
	 * i in [0,h[
	 * j in [0,w[
	 */
	void colorIJ(uchar4* ptrColor , int i , int j , int t)
	    {
	    uchar levelGris;

	    f(&levelGris, i, j, t); // update levelGris

	    ptrColor->x = levelGris;
	    ptrColor->y = levelGris;
	    ptrColor->z = levelGris;

	    ptrColor->w = 255; // opaque
	    }

    private:

	void f(uchar* ptrLevelGris , int i , int j , int t)
	    {
	    *ptrLevelGris = 255 * (i + t) / (float)h;
	    }

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	int h;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 /*----------------------------------------------------------------------*/
