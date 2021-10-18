#pragma once

#include <math.h>
#include <cuda_fp16.h>

#include "real.h"
#include "Maths.h"

#include "DomaineMath_GPU.h"
#include "Colors_GPU.h"
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
	    // TODO Mandelbrot GPU

	    // Calculer la suite en (x,y)
	    int ki = suite(x,y);
	    // Colorier
	    if (ki < this->n)//si ca diverge (c.a.d k<=n) => colorier
		{
		real hue = (1.f*ki)/this->n;// h ( k ) = (1/n)*k, convertir en hue, cf. formule TP page 10
		Colors::HSB_TO_RVB(hue, ptrColorIJ);//colorier pixel IJ
		}
	    else //sinon, colorier en noir
		{
		ptrColorIJ->x = 0;
		ptrColorIJ->y = 0;
		ptrColorIJ->z = 0;
		ptrColorIJ->w = 255;
		}
	    // Conseil:
	    // 		Etape 1 : 	Commencer par afficher une image uniforme grise (128 par exemple)
	    // 				pour valider tout le pipeline en amont
	    //
	    // 		Etape 2:	Puis une fois que l'image grise est valider, attaquer montecarlo

	    // debug temp
	    //		{
//	    		ptrColorIJ->x = 128;
//	    		ptrColorIJ->y = 128;
//	    		ptrColorIJ->z = 128;
//	    		ptrColorIJ->w = 255; // opacity facultatif

	    //		}
	    }

    private:

	/**
	 * Warning: define real in real.h (real=float or real=double or real= half)
	 */
	__inline__
	__device__
	int suite(real x , real y)
	    {
	    // TODO Mandelbrot GPU

	    // Utiliser dans vos formules les variable :
	    //
	    //		DEUX
	    //		QUATTRE
	    //		ZERO
	    //
	    // definit au debut de ce fichier. Est-utile pour  passer facilement d'une version fp64 (double) fp32(float) fp16(half)

	    // Calculer la suite en (x,y) jusqu'à n, à moins que critere arret soit atteint avant
	    // return le nombre d'element de la suite calculer
	    real a = ZERO;//Initialisation
	    real b = ZERO;//Initialisation, c.f. TP page 9
	    int k = 0;
	    real aCopy = ZERO;
	    bool stopCond1 = k>n;//condition d'arret 1
	    bool stopCond2 = (a*a + b*b)>QUATRE;//condition d'arret 2
	    while (!stopCond1 && !stopCond2)
//	    while (!k>n && !((a*a+b*b)>QUATRE))
		{
		aCopy = a;
		a = a*a - b*b + x;
		b = DEUX * aCopy * b + y;
		k++;
		stopCond1 = k>n;//update stop condition 1
		stopCond2 = (a*a+b*b)>QUATRE;//update stop condition 2
		}
	    return k;
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
