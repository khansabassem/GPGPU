#include "EventProvider.h"

#include "VagueProvider.h"
#include "ImageCustomEvent.h"

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
Animable_I<uchar4>* EventProvider::createAnimable(bool isVerbose)
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable(isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* EventProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Image_I* EventProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageCustomEvent(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* EventProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* EventProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
