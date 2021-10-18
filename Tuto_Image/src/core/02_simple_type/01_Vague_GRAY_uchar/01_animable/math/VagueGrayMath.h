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
class VagueGrayMath
    {

	/*--------------------------------------*\
	 |*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	VagueGrayMath(int w , int h) :
		h(h)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans VagueMath

	virtual ~VagueGrayMath(void)
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
	void colorIJ(uchar* ptrLevelGris , int i , int j , int t)
	    {
	    *ptrLevelGris = 255 * (i + t) / (float)h;
	    }

    private:

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
