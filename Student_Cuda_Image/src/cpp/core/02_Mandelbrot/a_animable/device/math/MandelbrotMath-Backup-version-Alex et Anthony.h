#pragma once

#include <math.h>
#include <cuda_fp16.h>

#include "real.h"
#include "Maths.h"

#include "DomaineMath_GPU.h"
#include "Colors_GPU.h"
#include "Calibreur_GPU.h"
using namespace gpu;

/*--------------------------------------*\
 |*		Helper type		*|
 \*-------------------------------------*/

#ifdef MANDELBROT_HALF
#define DEUX (half)2
#define QUATRE (half)4
#define ZERO (half)0
#endif

#ifdef MANDELBROT_FLOAT
#define DEUX 2.f
#define QUATRE 4.f
#define ZERO 0.f
#endif

#ifdef MANDELBROT_DOUBLE
#define DEUX 2.0
#define QUATRE 4.0
#define ZERO 0.0
#endif

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

class MandelbrotMath
    {
	/*--------------------------------------*\
	|*		Constructeur		*|
	 \*-------------------------------------*/

    public:

	__device__ MandelbrotMath(int n) :
		n(n)
	    {
	    //
	    }

	__device__
	     virtual ~MandelbrotMath(void)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColorIJ , real x , real y)
	    {
	    Calibreur<real> calibreur(Interval<real>(0, n - 1), Interval<real>(0, 1));

	    real z = suite(x, y);

	    if (z < (real)n)
		{

		real hue01 = z;
		calibreur.calibrer(&hue01);

		Colors::HSB_TO_RVB(hue01, ptrColorIJ); // update color

		ptrColorIJ->w = 255; //opaque
		}
	    }

    private:

	/**
	 * Warning: define real in real.h (real=float or real=double or real= half)
	 */
	__inline__
	__device__
	int suite(real x , real y)
	    {
	    real a = ZERO;
	    real b = ZERO;

	    int i = 0;

	    while(i<=n)
		{
		real aCopy = a;
		a = ((a*a) - (b*b)) + x;
		b = (DEUX * aCopy * b)+ y;

		if((a*a) + (b*b) > QUATRE) break;
		i++;
		}

	    return i;
	    }

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	int n;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
