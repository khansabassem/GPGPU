#include "AddVectorProviderBig.h"

#include "AddVectorBigUse.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * override
 * Mandatory : delete yourself UseGPU_I*
 */
Use_I* AddVectorProviderBig::createUse(const Grid& grid,bool isVerbose)
    {
    return new AddVectorBigUse(grid,isVerbose);
    }

/**
 * override
 * Mandatory : delete yourself UseGPU_I*
 */
Use_I* AddVectorProviderBig::createUse(bool isVerbose)
    {
    return new AddVectorBigUse(isVerbose);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
