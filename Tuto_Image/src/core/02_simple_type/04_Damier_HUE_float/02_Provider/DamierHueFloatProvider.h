#pragma once

#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"

using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierHueFloatProvider: public Provider_I<float>
    {
    public:

	/**
	 * Override
	 */
	Animable_I<float>* createAnimable(void);

	/**
	 * Override
	 */
	Image_I* createImageGL(void);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

