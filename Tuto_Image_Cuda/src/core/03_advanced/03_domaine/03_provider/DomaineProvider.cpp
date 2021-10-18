#include "DomaineProvider.h"
#include "DamierProvider.h"
#include "ImageCustomDomaine.h"

#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

#include "DomaineMath_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* DomaineProvider::createAnimable(bool isVerbose)
    {
    DamierProvider damierProvider;
    return damierProvider.createAnimable(isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* DomaineProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DamierProvider damierProvider;
    return damierProvider.createAnimable(grid, isVerbose);
    }

Image_I* DomaineProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageCustomDomaine(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* DomaineProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* DomaineProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
