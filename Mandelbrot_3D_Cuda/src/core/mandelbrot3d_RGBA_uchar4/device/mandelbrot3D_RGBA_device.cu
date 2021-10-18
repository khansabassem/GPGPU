#include "Mandelbrot3DMath_RGBA.h"
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

__global__ void mandelbrot3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , int n);

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
__global__ void mandelbrot3DCuda(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , int w , int h , DomainMath3D domaineMath , int n)
    {
    Mandelbrot3DMath_RGBA mandelbrotMath(n);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    const int WH = w * h;

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
    float hue;
    while (s < WH)
	{
	Indices::toIJ(s, w, &vertexI, &vertexJ); // update (vertexI, vertexJ)

	domaineMath.toXY(DX, DY, vertexI, vertexJ, &x, &y);


	mandelbrotMath.colorXY(&color , &hue, x , y);
	mandelbrotMath.sommetXY(&sommet, hue,x, y);

	tabVerticesColorGM[s] = color;
	tabVerticesXYZGM[s] = sommet;

	s += NB_THREAD;
	}

    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

