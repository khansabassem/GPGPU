#include "RaytracingProviderGM.h"

#include "RaytracingCreator.h"
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
Animable_I<uchar4>* RaytracingProviderGM::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    dim3 dg(68, 1, 1);
    dim3 db(512, 1, 1);
    Grid grid(dg, db);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* RaytracingProviderGM::createAnimable(const Grid& grid , bool isVerbose)
    {
    return RaytracingCreator::createGM(grid, isVerbose);
    }

/**
 * Override
 */
Image_I* RaytracingProviderGM::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* RaytracingProviderGM::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* RaytracingProviderGM::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
