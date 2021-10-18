#include "VagueProvider.h"
#include "Vague.h"

#include "Maths.h"

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
Animable_I<uchar4>* VagueProvider::createAnimable(void)
    {
    // Animation
    int dt = 1;

    // Dimension
    int dw = 16 * 32 * 2;
    int dh = 16 * 32;

    return new Vague(dw, dh, dt);
    }

/**
 * Override
 */
Image_I* VagueProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
