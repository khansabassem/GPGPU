#include "Maths.h"

#include "VagueGrayProvider.h"
#include "VagueGray.h"

#include "ImageAnimable_CPU.h"

using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar>* VagueGrayProvider::createAnimable(void)
    {
    // Animation
    int dt = 1;

    // Dimension
    int w = 16 * 32 * 2;
    int h = 16 * 32;

    return new VagueGray(w, h, dt);
    }

/**
 * Override
 */
Image_I* VagueGrayProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageAnimable_GRAY_uchar(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
