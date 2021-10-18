#pragma once

#include "cudas.h"

#include "ProviderUse_I.h"
#include "Provider_I_GPU.h"

using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class MandelbrotProvider: public Provider_I<uchar4>, ProviderUse_I
    {
    public:

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(bool isVerbose = true);

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(const Grid& grid , bool isVerbose = false);

	/**
	 * Override
	 */
	virtual Image_I* createImageGL();

	/**
	 * Override
	 */
	virtual Use_I* createUse(const Grid& grid , bool isVerbose = false);

	/**
	 * Override
	 */
	virtual Use_I* createUse(bool isVerbose = true);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

