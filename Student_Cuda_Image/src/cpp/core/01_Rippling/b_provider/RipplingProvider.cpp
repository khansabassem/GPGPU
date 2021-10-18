#include "RipplingProvider.h"
#include "Rippling.h"

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
Animable_I<uchar4>* RipplingProvider::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    dim3 dg = dim3(MP,1,1);//68
    dim3 db = dim3(CORE_MP,16,1); //1024
    Grid grid(dg,db,1);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* RipplingProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    float dt = 2 * PI / 10;

    // Dimension
    int w = 16 * 60;
    int h = 16 * 60;

    return new Rippling(grid, w, h, dt, isVerbose);
    }

/**
 * Override
 */
Image_I* RipplingProvider::createImageGL()
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* RipplingProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* RipplingProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
