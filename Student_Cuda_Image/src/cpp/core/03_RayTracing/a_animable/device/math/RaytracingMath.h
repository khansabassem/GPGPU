#pragma once

#include <math.h>
#include "Maths.h"
#include "Limits.h"

#include "Sphere.h"
#define FLOAT_MAX 1e+6

#include "Colors_GPU.h"
using namespace gpu;

class RaytracingMath
    {
    public:

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

	__device__ RaytracingMath(Sphere* tabSpheresDev , int nbSpheres , float t) : //
		tabSpheresDev(tabSpheresDev), //
		nbSpheres(nbSpheres), //
		t(t)
	    {
	    }

	__device__              virtual ~RaytracingMath()
	    {
	    // rien
	    }

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	__device__
	void colorXY(uchar4* ptrColorIJ , int i , int j)
	    {
	    float2 xySol;
	    xySol.x = i;
	    xySol.y = j;

	    colorXY(xySol, ptrColorIJ); // update ptrColorIJ

	    ptrColorIJ->w = 255; // opacity facultatif

	    // Conseil:
	    // 		Etape 1 : 	Commencer par afficher une image uniforme grise (128 par exemple)
	    // 				pour valider tout le pipeline en amont
	    //
	    // 		Etape 2:	Puis une fois que l'image grise est valider, attaquer raytracing
	    }

    private:

	__inline__
	__device__
	void colorXY(const float2& xySol , uchar4* ptrColorXY)
	    {
	    // TODO Raytracing GPU math
	    // process the color for the pixel (x,y)
	    // use methode of classe Sphere
	    //tabSpheresDev
	    // nbSpheres
	    int indexClosest = 0;
	    float closestSphereDistance = FLOAT_MAX;
	    float brightnessNearest = 0;

	    int i = 0;

	    while(i < nbSpheres)
		{
		Sphere* currentSphere = &tabSpheresDev[i];
		const float currentH2 = currentSphere->h2(xySol);
		const bool isBelow = currentSphere->isEnDessous(currentH2);
		// const int belowInt = (int)isBelow;
		// currentDistance = belowInt*currentDistance+( (belowInt%1)*FLOAT_MAX );
		if(isBelow)
		    {
		    const float currentDZ = currentSphere->dz(currentH2);
		    const float currentDistance = currentSphere->distance(currentDZ);

		    if(currentDistance < closestSphereDistance)
			{
			closestSphereDistance = currentDistance;
			indexClosest = i;
			brightnessNearest = currentSphere->brightness(currentDZ);
			}
		    }
		i++;
		}

	    Colors::HSB_TO_RVB((&tabSpheresDev[indexClosest])->hue(t), 1, brightnessNearest, ptrColorXY);

	    }

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

// Input
	Sphere* tabSpheresDev;
	int nbSpheres;
	float t;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
