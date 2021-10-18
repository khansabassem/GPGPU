#include "HeatTransferProviderGM.h"

#include "HeatTransfer.h"

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
Animable_I<uchar4>* HeatTransferProviderGM::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    //FLOAT Real
    dim3 dg = dim3(204, 1, 1); //
    dim3 db = dim3(256, 1, 1); //

    //DOUBLE Real
//    dim3 dg = dim3(204, 1, 1); //
//    dim3 db = dim3(128, 1, 1); //

    //Half Real
//    dim3 dg = dim3(204, 1, 1); //
//    dim3 db = dim3(128, 1, 1); //
    Grid grid(dg, db, 1);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* HeatTransferProviderGM::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    float dt = 2 * PI / 10;

    // Dimension
    int w = 16 * 60; // 960
    int h = 16 * 60; // 960
    HeaterPoint* heatersQueue = new HeaterPoint;

    int* ptrWindStrength = new int;
    *ptrWindStrength = 1;

    WindDirection* ptrWindDirection = new WindDirection;
    *ptrWindDirection = WindDirection::ANY;
    return new HeatTransfer(grid, w, h, dt, isVerbose, heatersQueue, ptrWindStrength, ptrWindDirection);
    }

/**
 * Override
 */
Image_I* HeatTransferProviderGM::createImageGL()
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* HeatTransferProviderGM::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* HeatTransferProviderGM::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
