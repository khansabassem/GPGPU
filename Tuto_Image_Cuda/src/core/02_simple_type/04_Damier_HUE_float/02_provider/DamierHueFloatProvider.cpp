#include "DamierHueFloatProvider.h"
#include "DamierHueFloat.h"

#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

#include "DomaineMath_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<float>* DamierHueFloatProvider::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // A optimiser
    dim3 dg(MP, 2, 1);
    dim3 db(CORE_MP, 4, 1);
    Grid grid(dg, db);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<float>* DamierHueFloatProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DomaineMath domaineMath(0, 0, 2 * PI, 2 * PI);

    // Animation;
    float dt = 2 * PI / 2000;
    int n = 2;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new DamierHueFloat(grid, w, h, dt, n, domaineMath, isVerbose);
    }

/**
 * Override
 */
Image_I* DamierHueFloatProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_HUE_float(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* DamierHueFloatProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<float>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* DamierHueFloatProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<float>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
