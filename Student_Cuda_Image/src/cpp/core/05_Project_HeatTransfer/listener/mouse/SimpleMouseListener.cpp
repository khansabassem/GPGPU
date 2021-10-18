#include "SimpleMouseListener.h"

#include <iostream>
#include "HeatTransfer.h"
#include "HeaterPoint.h"
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

static HeaterPoint* ptrQueue;

SimpleMouseListener::SimpleMouseListener(HeaterPoint* heatersQueue)
    {
    ptrQueue = heatersQueue;
    }

SimpleMouseListener::~SimpleMouseListener()
    {
    //rien
    }

/*-----------------------*\
|*	Methode  	*|
 \*----------------------*/

void SimpleMouseListener::onMouseMoved(const MouseEvent& event)
    {
    HeaterPoint point =
	{
	event.getX(), event.getY()
	};
    ptrQueue[0] = point;
    }

void SimpleMouseListener::onMousePressed(const MouseEvent& event)
    {
    HeaterPoint point =
	{
	event.getX(), event.getY()
	};
    ptrQueue[0] = point;
    }

void SimpleMouseListener::onMouseReleased(const MouseEvent& event)
    {
    // Rien
    }

void SimpleMouseListener::onMouseWheel(const MouseWheelEvent& event)
    {
    // Rien
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * (x,y) : coordonn�e image, et non frame!
 */
void SimpleMouseListener::printXY(const MouseEvent& event)
    {
    // Rien
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

