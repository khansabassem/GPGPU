#include "Mandelbrot3D_RGBA.h"

#include <assert.h>

#include "Maths.h"
#include "cudas.h"

using std::to_string;

using gpu::DomainMath3D;
using gpu::SurfaceStrip_RGBA_uchar4;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void mandelbrot3DCuda(float3* tabVerticesXYZGM, uchar4* tabVerticesColorGM, int w, int h, DomainMath3D domaineMath, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

Mandelbrot3D_RGBA::Mandelbrot3D_RGBA(const Grid& grid , int w , int h , const DomainMath3D& domaineMath , float dt , int n) :
	// Parent
	SurfaceStrip_RGBA_uchar4(w, h, domaineMath), //
	// Inputs
	n(n), //
	dg(grid.dg), //
	db(grid.db), //
	// Tools
	variateurT(Interval<int>(20, 120), 1)
    {
    // Tools
    this->title = "Mandelbrot3D_RGBA_uchar4";
    this->t = 0;
    }

Mandelbrot3D_RGBA::~Mandelbrot3D_RGBA()
    {
    // rien
    }

/*-------------------------*\
 |*	Surcharge	   *|
 \*------------------------*/

/**
 * Override
 * Call periodicly by the api
 */
void Mandelbrot3D_RGBA::fillVertex(float3* tabVerticesXYZGM , uchar4* tabVerticesColorGM , unsigned int w , unsigned int h , const gpu::DomainMath3D& domaineMath)
    {

    int n = t;
mandelbrot3DCuda<<<dg,db>>>(tabVerticesXYZGM,tabVerticesColorGM,w,h,domaineMath,n);

}

/**
 * Override
 * Call periodicly by the api
 */
void Mandelbrot3D_RGBA::animationStep(bool& isNeedUpdate)
{
this->t = variateurT.varierAndGet(); // in [0,2pi]
}

/**
 * Override
 * Call periodicly by the api
 */
void Mandelbrot3D_RGBA::paintPrimitives(Graphic2D& graphic2D)
{
graphic2D.setFont(TIMES_ROMAN_24);

float r = 0.5f;
float g = 0.5f;
float b = 0.5f;

graphic2D.setColorRGB(r, g, b);

// TOP : Para Animation
    {
    string message = "t = " + to_string(t);
    graphic2D.drawTitleTop(message);
    }

// BOTTOM : Title
    {
    graphic2D.drawTitleBottom(title);
    }
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

