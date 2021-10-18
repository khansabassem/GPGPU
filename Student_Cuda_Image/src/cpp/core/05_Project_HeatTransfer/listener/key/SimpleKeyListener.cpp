#include "SimpleKeyListener.h"
#include "WindDirection.h"
#include <iostream>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-----------------------*\
|*	Constructor  	*|
 \*----------------------*/
static int* ptrWindStrength;
static WindDirection* ptrWindDirection;

SimpleKeyListener::SimpleKeyListener(int* windStrength , WindDirection* windDirection)
    {
    ptrWindStrength = windStrength;
    ptrWindDirection = windDirection;
    }

SimpleKeyListener::~SimpleKeyListener()
    {
    //rien
    }

/*-----------------------*\
|*	Methode  	*|
 \*----------------------*/

void SimpleKeyListener::onKeyPressed(const KeyEvent& event)
    {
    // Rien
    }

void SimpleKeyListener::onKeyReleased(const KeyEvent& event)
    {
    if (event.isSpecial())
	{
	int key = event.getSpecialKey();

	switch (key)
	    {
	case 14:
	    // Up
	    *ptrWindStrength += 1;
	    break;

	case 16:
	    // Down
	    *ptrWindStrength = 1;
	    break;
	    }

	}

    switch (event.getKey())
	{
    case 'u':
	*ptrWindDirection = WindDirection::NORTH;
	break;
    case 'h':
	*ptrWindDirection = WindDirection::WEST;
	break;
    case 'j':
	*ptrWindDirection = WindDirection::SOUTH;
	break;
    case 'k':
	*ptrWindDirection = WindDirection::EAST;
	break;
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

