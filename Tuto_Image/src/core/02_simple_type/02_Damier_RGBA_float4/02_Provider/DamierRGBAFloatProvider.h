#pragma once

#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"

using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DamierRGBAFloatProvider: public Provider_I<float4>
    {
    public:

	/**
	 * Override
	 */
	Animable_I<float4>* createAnimable(void);

	/**
	 * Override
	 */
	Image_I* createImageGL(void);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

