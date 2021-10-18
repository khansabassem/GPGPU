#include "VagueGrayProvider.h"
#include "VagueGray.h"

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
Animable_I<uchar>* VagueGrayProvider::createAnimable(bool isVerbose)
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    // disons a optimiser
    dim3 dg(MP, 1 ,1);
    dim3 db(CORE_MP, 14, 1);
    Grid grid(dg, db);

    return createAnimable(grid, isVerbose);
    }

/**
 * Override
 */
Animable_I<uchar>* VagueGrayProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    int dt = 1;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new VagueGray(grid, w, h, dt, isVerbose);
    }

/**
 * Override
 */
Image_I* VagueGrayProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageAnimable_GRAY_uchar(createAnimable(), colorTexte);
    }

/**
 * override
 */
Use_I* VagueGrayProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* VagueGrayProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar>(this, isVerbose);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
