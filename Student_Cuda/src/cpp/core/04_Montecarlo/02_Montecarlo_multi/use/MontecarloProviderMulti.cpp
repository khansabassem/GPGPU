#include "MontecarloProviderMulti.h"

#include "MontecarloMultiUse.h"
#include "MontecarloUseTools.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeurs		*|
 \*-------------------------------------*/

MontecarloProviderMulti::MontecarloProviderMulti(float h,entier nbDar) ://
	h(h),//
	nbDar(nbDar)
    {
    // rien
    }

MontecarloProviderMulti::MontecarloProviderMulti()://
	MontecarloProviderMulti(MontecarloUseTools::H,MontecarloUseTools::nbDarTotalUse())
    {
    // rien
    }



MontecarloProviderMulti::~MontecarloProviderMulti()
    {
    // rien
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/**
 * override
 * Mandatory : delete yourself UseGPU_I*
 */
Use_I* MontecarloProviderMulti::createUse(const Grid& grid,bool isVerbose)
    {
    return new MontecarloMultiUse(grid, isVerbose,nbDar,h);
    }

/**
 * override
 * Mandatory : delete yourself UseGPU_I*
 */
Use_I* MontecarloProviderMulti::createUse(bool isVerbose)
    {
    return new MontecarloMultiUse(isVerbose,nbDar,h);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
