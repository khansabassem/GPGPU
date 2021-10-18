#include "EventProvider.h"

#include "HeatTransferProviderGM.h"
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

static HeatTransfer* heatTrans;
/**
 * Override
 */
Animable_I<uchar4>* EventProvider::createAnimable(bool isVerbose)
    {
    HeatTransferProviderGM provider;
    Animable_I<uchar4>* toReturn = provider.createAnimable(isVerbose);
    heatTrans = (HeatTransfer*)toReturn;
    if (heatTrans == NULL)
	{
	std::cerr << "heatTrans is null" << std::endl;
	}

    return toReturn;
    }

/**
 * Override
 */
Animable_I<uchar4>* EventProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    HeatTransferProviderGM provider;
    Animable_I<uchar4>* toReturn = provider.createAnimable(grid, isVerbose);
    heatTrans = (HeatTransfer*)toReturn;
    assert(heatTrans != NULL);

    return toReturn;
    }

/**
 * Override
 */
Image_I* EventProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // Green
    return new ImageCustomEvent(createAnimable(), colorTexte, heatTrans->getHeaterQueue(), heatTrans->getWindStrength(), heatTrans->getWindDirection());
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
