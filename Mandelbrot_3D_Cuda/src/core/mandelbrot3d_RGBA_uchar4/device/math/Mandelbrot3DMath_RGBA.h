#pragma once

#include <math.h>
#include <cuda_fp16.h>

#include "DomaineMath_GPU.h"
#include "Colors_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Mandelbrot3DMath_RGBA
    {
	const int NB_LOG = 8;

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ Mandelbrot3DMath_RGBA(int n) :
		n(n)
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void sommetXY(float3* ptrSommet , float hue , float x , float y)
	    {
	    // amélioration 2
	    ptrSommet->x = x;
	    ptrSommet->y = y;
	    ptrSommet->z = logs(hue, NB_LOG) + 0.5f;
	    }

	__device__
	float logs(float h01 , const int M)
	    {
	    float z = h01;
	    for (int i = 0; i <= M; i++)
		{
		z = log(z + 1.0f);
		}
	    return z;
	    }

	__device__
	void colorXY(uchar4* ptrColorIJ , float* ptrHue , float x , float y)
	    {
	    // de base en noire
	    ptrColorIJ->x = 0;
	    ptrColorIJ->y = 0;
	    ptrColorIJ->z = 0;
	    ptrColorIJ->w = 255; //transparent
	    *ptrHue = 0;
	    // Calculer la suite en (x,y)
	    int ki = suite(x, y);
	    // Colorier
	    if (ki <= this->n)	//si ca diverge (c.a.d k<=n) => colorier
		{
		const float hue = (1.f * ki) / this->n;	// h ( k ) = (1/n)*k, convertir en hue, cf. formule TP page 10
		*ptrHue = hue;
		Colors::HSB_TO_RVB(hue, ptrColorIJ);	//colorier pixel IJ
		}
	    }
    private:

	__inline__
	__device__
	int suite(float x , float y)
	    {

	    float a = 0.0; //Initialisation ZERO
	    float b = 0.0;//Initialisation, c.f. TP page 9
	    int k = 0;
	    float aCopy = 0.0;
	    bool stopCond1 = k>n;//condition d'arret 1
	    bool stopCond2 = (a*a + b*b)>4.f;//condition d'arret 2
	    while (!stopCond1 && !stopCond2)
		{
		aCopy = a;
		a = a*a - b*b + x;
		b = 2.f * aCopy * b + y;
		k++;
		stopCond1 = k>n; //update stop condition 1
		stopCond2 = (a*a+b*b)>4.f;//update stop condition 2
		}
	    return k;
	    }

	/*--------------------------------------*\
    	|*		Attribut		*|
	 \*-------------------------------------*/

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
