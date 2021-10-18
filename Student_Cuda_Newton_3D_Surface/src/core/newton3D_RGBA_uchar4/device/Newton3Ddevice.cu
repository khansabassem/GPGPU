#include "Newton3DMath.h"
#include "Thread2D.h"
#include "Indices_GPU.h"
#include "DomainMath3D_GPU.h"
#include "cudas.h"


using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void newton3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * w nbPoint en x
 * h nbPoint en y
 */
__global__ void newton3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , int n)
    {
    float epsilon =0.1f*powf(0.90f,n);// 0.1f;

    Newton3DMath_RGBA newtonMath(epsilon, n);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    const int WH = w * h;

//    uchar4 colorxy;// by me
    uchar4 color;
    float3 sommet;

    float x;
    float y;
    float DX;
    float DY;

    int vertexI;
    int vertexJ;

    domaineMath.delta(w, h, &DX, &DY);

    int s = TID;
    float hue, sat, val;

    while (s < WH)
	{
	Indices::toIJ(s, w, &vertexI, &vertexJ); // update (vertexI, vertexJ)

	domaineMath.toXY(DX, DY, vertexI, vertexJ, &x, &y);

	newtonMath.colorXY(&color, x, y);//couleur en format RVB
	newtonMath.RGBtoHUE( color.x, color.y, color.z, &hue, &sat, &val);
//	printf("hue : %f \n sat: %f\n, val: %f\n", hue, sat, val);
	newtonMath.sommetXY(&sommet, hue, sat, val, x, y);//RVB -> HSB,  puis extraire la valeur de sommet selon the Hue de HSB.


	tabVerticesColorGM[s] = color;
	tabVerticesXYZGM[s] = sommet;

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

