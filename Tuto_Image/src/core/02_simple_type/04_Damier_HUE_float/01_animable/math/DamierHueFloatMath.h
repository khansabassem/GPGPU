#pragma once

#include <math.h>
#include "Maths.h"

#include "Calibreur_CPU.h"
#include "Colors_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierHueFloatMath
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	DamierHueFloatMath(uint n) :
		calibreur(Interval<float>(-1, 1), Interval<float>(0, 1)), //
		n(n)
	    {
	    // rien
	    }

	// constructeur copie automatique car pas pointeur dans
	//	DamierMath
	// 	calibreur
	// 	IntervalF

	virtual ~DamierHueFloatMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	void colorXY(float* ptrColor , float x , float y , float t)
	    {
	    float z = f(x, y, t);

	    float hue01 = z;
	    calibreur.calibrer(&hue01);

	    *ptrColor = hue01;
	    }

    private:

	float f(float x , float y , float t)
	    {
	    return sinf(x * n + t) * cosf(y * n + t);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	uint n;

	// Tools
	Calibreur<float> calibreur;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
