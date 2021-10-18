#pragma once

#include "Provider_I_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class DomaineProvider: public Provider_I<uchar4>
    {
    public:

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(void);

	/**
	 * Override
	 */
	virtual Image_I* createImageGL(void);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

