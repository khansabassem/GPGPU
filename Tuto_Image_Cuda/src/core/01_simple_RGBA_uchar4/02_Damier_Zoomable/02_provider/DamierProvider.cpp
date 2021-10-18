#include "DamierProvider.h"
#include "Damier.h"

#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

#include "DomaineMath_GPU.h"
using gpu::DomaineMath;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* DamierProvider::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // disons a optimiser
    dim3 dg(MP, 2, 1);
    dim3 db(CORE_MP, 2, 1);
    Grid grid(dg, db);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar4>* DamierProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    DomaineMath domaineMath(0, 0, 2 * PI, 2 * PI);

    // Animation;
    float dt = 2 * PI / 2000;
    int n = 2;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new Damier(grid, w, h, dt, n, domaineMath, isVerbose);
    }

/**
 * Override
 */
Image_I* DamierProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* DamierProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* DamierProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
