#include "EventProvider.h"

#include "VagueProvider.h"
#include "ImageCustomEvent.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* EventProvider::createAnimable()
    {
    VagueProvider vagueProvider;
    return vagueProvider.createAnimable();
    }

/**
 * Override
 */
Image_I* EventProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageCustomEvent(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
