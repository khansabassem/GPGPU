#pragma once

#include "KeyListener_I.h"
#include "WindDirection.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class SimpleKeyListener: public KeyListener_I
    {
    public:

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

	SimpleKeyListener(int* windStrength , WindDirection* windDirection);
	virtual ~SimpleKeyListener();

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Override
	 */
	virtual void onKeyPressed(const KeyEvent& event);

	/**
	 * Override
	 */
	virtual void onKeyReleased(const KeyEvent& event);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
