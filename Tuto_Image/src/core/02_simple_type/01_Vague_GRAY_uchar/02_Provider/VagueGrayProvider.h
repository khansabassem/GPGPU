#pragma once

#include "Animable_I_CPU.h"
#include "Provider_I_CPU.h"

using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class VagueGrayProvider: public Provider_I<uchar>
    {
    public:

	/**
	 * Override
	 */
	Animable_I<uchar>* createAnimable(void);

	/**
	 * Override
	 */
	Image_I* createImageGL(void);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

