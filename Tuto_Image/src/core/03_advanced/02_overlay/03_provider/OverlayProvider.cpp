#include "OverlayProvider.h"

#include "ImageOverlay.h"
#include "VagueProvider.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* OverlayProvider::createAnimable()
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable();
    }

/**
 * Override
 */
Image_I* OverlayProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageOverlay(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
