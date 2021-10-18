#include "OverlayProvider.h"

#include "VagueProvider.h"
#include "ImageOverlay.h"

#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* OverlayProvider::createAnimable(bool isVerbose)
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable(isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* OverlayProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Image_I* OverlayProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageOverlay(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* OverlayProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* OverlayProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
