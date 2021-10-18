#include "MandelbrotProvider.h"
#include "Mandelbrot.h"

#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

#include <assert.h>

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Override		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
//  Float
//    dim3 dg = dim3(136, 1, 1);
//    dim3 db = dim3(128, 1, 1);

////  Double
//    dim3 dg = dim3(68, 1, 1);
//    dim3 db = dim3(320, 1, 1);

//  Half
    dim3 dg = dim3(68, 1, 1);
    dim3 db = dim3(384, 1, 1);

    Grid grid(dg, db);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* MandelbrotProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    int nMin = 20; // 100
    int nMax = 120; // 100

    // Domaine init
    double x1 = -2.1;
    double y1 = -1.3;
    double x2 = 0.8;
    double y2 = 1.3;
    DomaineMath domaineMath(x1, y1, x2, y2);

    // Dimension
    int w = 16 * 80;
    int h = 16 * 60;

    return new Mandelbrot(grid, w, h, domaineMath, isVerbose, nMin, nMax);
    }

/**
 * Override
 */
Image_I* MandelbrotProvider::createImageGL()
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* MandelbrotProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* MandelbrotProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
