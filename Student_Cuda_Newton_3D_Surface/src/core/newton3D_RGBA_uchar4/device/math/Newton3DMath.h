#pragma once

#include <math.h>
#include <stdio.h>
#include "Calibreur_GPU.h"
#include "Colors_GPU.h"

using namespace gpu;

#include <cfloat>


/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Newton3DMath_RGBA
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	__device__ Newton3DMath_RGBA(float epsilon, int n)
	    {

	    this->epsilon = epsilon;
	    this->n = n;
	    this->colorFactor = 25; //for No Dimming=>0; used to force to update the color

	    XA1 = 1;
	    XA2 = 0;

	    XB1 = -0.5f;
	    XB2 = sqrtf(3) / 2.0f;

	    XC1 = -0.5f;
	    XC2 = -sqrtf(3) / 2.0f;
	    }


	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void sommetXY(float3* ptrSommet , float h,float s,float v, float x , float y)//, float t)

	    {

//
//	On choisit ici celui basé sur la couleur HSB.
//	On associe une hauteur selon la valeur de la hue, qui rappelons-le appartient à l’intervalle [0,1].
//	Le noir sera mappé sur la hauteur 0.
//	Le total de la hauteur de l’image vivra ainsi dans [0,1]
//	Pour affirmer les premiers palliers, et éviter des raffales de pics on utilisera d’abord
//	le log sur la hue01.

//	--float z = log( hsv + 1 ) + 0.5;
//	float z = f(hsv);
//	On additionne finalement 1 pour éviter une valeur finale négative. Le 0.5 est là pour
//	détacher le fond noir du fractale.
//	    float z = f(x, y, t); uchar4
//	    float hue = 0.f;
//
//	    hue = RGBtoHUE((float)color.x, (float)color.y, (float)color.z);
//	    float z = f(hue);
	    float hsv = (h+s+v)/765;

	    ptrSommet->x = x;
	    ptrSommet->y = y;
	    ptrSommet->z = f(hsv);//z;//(h+s+v)/765; //z;
//	    printf("Hue %f \n",ptrSommet->z );

	    }

	__device__
	float f(float h01)
	{
	    const int M = 8;//1 ou 8 (ici fixe)
	    return logs(h01, M) + 0.5f;
	}
	__device__
	float logs(float h01, const int M)
	{
	    float z = h01;
	    for (int i = 0; i <= M; i++)
	    {
		z = log(z + 1.0f);
	    }
	    return z;
	}
	__device__
	void RGBtoHUE( float r, float g, float b, float* h, float* s, float* v)//, float *h, float *s, float *v )
	{
		float mint, maxt, delta;
		mint = min( r, min(g, b ));
		maxt = max( r, max(g, b ));
		*v = maxt;				// v
//		hsb.z = max;
		delta = maxt - mint;
		if( maxt != 0 )
			*s = delta / maxt;		// s
//		    hsb.y = delta/maxt

		else {
//			 r = g = b = 0	;	// s = 0, v is undefined
			*s = 0;
//			hsb.y = 0.f ;
//			hsb.x = -1;
			 *h = -1;
			return;
		}
		if( r == maxt )
			*h = ( g - b ) / delta;		// between yellow & magenta
//			hsb.x = ( g - b ) / delta;
		else if( g == maxt )
			*h = 2 + ( b - r ) / delta;	// between cyan & yellow
//		   	hsb.x = 2 + ( b - r ) / delta;
		else
			*h = 4 + ( r - g ) / delta;	// between magenta & cyan
//			hsb.x = 4 + ( r - g ) / delta;
		*h *= 60;				// degrees
//		hsb.x *= 60;				// degrees

		if( *h < 0 )
			*h += 360;
//		return hsb;
	}



//	__device__
//	void colorZ(uchar4* ptrColorRGBA , float z)
//	    {
//	    calibreur.calibrer(&z);
//	    float hue01 = z;
//	    Colors::HSB_TO_RVB(hue01, ptrColorRGBA);
//	    }



    __device__
	    //void colorXY(uchar4* ptrColor , float x , float y , float t)
	    //by me
	    void colorXY(uchar4* ptrColor,float x1, float x2)

		{
    //	    float z = f(x, y);
    //
    //	    float hue01 = z;
    //	    calibreur.calibrer(&hue01);
    //
    //	    Colors::HSB_TO_RVB(hue01, ptrColor); // update color
    //
    //	    ptrColor->w = 255; // opaque
	    //by me
		int i = 0;
		bool converged = false;

		float x1Copy = x1;
		float x2Copy = x2;

		do
		    {
		    computeNextStep(x1Copy, x2Copy, &x1, &x2);
		    x1Copy = x1;
		    x2Copy = x2;
		    converged = hasConverged(x1, x2);
		    }
		while (i++ <= this->n && !converged);
		//converged=true;
		if (converged)
		    {
		    float distSolA = getNorme(x1 - XA1, x2 - XA2);
		    float distSolB = getNorme(x1 - XB1, x2 - XB2);
		    float distSolC = getNorme(x1 - XC1, x2 - XC2);

		    float colorEasing = ((i * this->colorFactor) % 255);
    //		colorEasing = 0.0f;
		    if (distSolA < distSolB && distSolA < distSolC)
			{
			// solA est la plus proche
			ptrColor->x = 255 - colorEasing;
			ptrColor->y = 0;
			ptrColor->z = 0;
			}
		    else if (distSolB < distSolC)
			{
			// solB est la plus proche
			ptrColor->x = 0;
			ptrColor->y = 255 - colorEasing;
			ptrColor->z = 0;
			}
		    else
			{
			//solC est la plus proche
			ptrColor->x = 0;
			ptrColor->y = 0;
			ptrColor->z = 255 - colorEasing;
			}
		    }
		else
		    {
		    ptrColor->x = 0;
		    ptrColor->y = 0;
		    ptrColor->z = 0;

		    }
		ptrColor->w = 255;
		}

	private:

    //	__device__
    //	float f(float x , float y)// , float t)
    //	    {
    ////	    return sinf(x * n + t) * cosf(y * n + t);
    //	    return sinf(x * n ) * cosf(y * n );
    //	    }
	    // MÃ©thode choisie: (S1) page 6, Ã  savoir: On s'arrete lorsqu'on est suffisament proche d'une solution.
	    __device__
	    bool hasConverged(float x1, float x2)
		{
		return isSolutionConverged(x1, x2, XA1, XA2) || isSolutionConverged(x1, x2, XB1, XB2) || isSolutionConverged(x1, x2, XC1, XC2);
		}

	    __device__
	    bool isSolutionConverged(float x1, float x2, float x1Sol, float x2Sol)
		{
		return (getNorme(x1 - x1Sol, x2 - x2Sol) / getNorme(x1Sol, x2Sol)) < this->epsilon;
		}
	    __device__
	    float getNorme(float x, float y)
		{
		return sqrtf(x * x + y * y);
		}

	    /// FONCTIONS NEWTON
	    __device__
	    float f1(float x1, float x2)
		{
		return x1 * x1 * x1 - 3.0f * x1 * x2 * x2 - 1.0f;
		}

	    __device__
	    float f2(float x1, float x2)
		{
		return x2 * x2 * x2 - 3.0f * x1 * x1 * x2;
		}

	    __device__
	    float d1f1(float x1, float x2)
		{
		return 3.0f * (x1 * x1 - x2 * x2);
		}

	    __device__
	    float d2f1(float x1, float x2)
		{
		return -6.0f * x1 * x2;
		}

	    __device__
	    float d1f2(float x1, float x2)
		{
		return d2f1(x1, x2);
		}

	    __device__
	    float d2f2(float x1, float x2)
		{
		return 3.0f * (x2 * x2 - x1 * x1);
		}

	    __device__
	    void computeNextStep(float x1, float x2, float* outX1, float* outX2)
		{
		float a = d1f1(x1, x2);
		float b = d1f2(x1, x2);
		float c = d2f1(x1, x2);
		float d = d2f2(x1, x2);
		float tmp = a * d - b  * c;
		    if (fabsf(tmp) > 1e-10f){
			    float inversedJacobian = 1.0f / tmp;

			    float sa = inversedJacobian * d;
			    float sb = -inversedJacobian * c;
			    float sc = -inversedJacobian * b;
			    float sd = inversedJacobian * a;

			    *outX1 = x1 - (sa * f1(x1, x2) + sc * f2(x1, x2));
			    *outX2 = x2 - (sb * f1(x1, x2) + sd * f2(x1, x2));
		    }
		}

    private:

	__device__
	float f(float x , float y , float t)
	    {
	    return sin(x * n + t) * cos(y * n + t);
	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Input
	int n;

	float epsilon;

	// Tools
	int colorFactor;

	float XA1;
	float XA2;

	float XB1;
	float XB2;

	float XC1;
	float XC2;

	// Tools
//	Calibreur<float> calibreur;



    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
