#include "ImageCustomEvent.h"

#include <iostream>

#include "SimpleKeyListener.h"
#include "SimpleMouseListener.h"

#include "HeaterPoint.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

ImageCustomEvent::ImageCustomEvent(Animable_I<uchar4>* ptrAnimable , ColorRGB_01 colorTexte , HeaterPoint* heatersQueue , int* windStrength ,
	WindDirection* windDirection) :
	ImageAnimable_RGBA_uchar4(ptrAnimable, colorTexte)
    {
    // Tools
    listener(heatersQueue, windStrength, windDirection);
    }

ImageCustomEvent::~ImageCustomEvent(void)
    {
    delete ptrKeyListener;
    delete ptrMouseListener;
    }

/*--------------------------------------*\
 |*		Methode 		*|
 \*-------------------------------------*/

/**
 * Override
 * call periodicly by the api
 */
void ImageCustomEvent::paintPrimitives(Graphic2D& graphic2D)
    {
    ImageAnimable_RGBA_uchar4::paintPrimitives(graphic2D);

    float r = 0;
    float g = 0;
    float b = 0;
    graphic2D.setColorRGB(r, g, b);
    graphic2D.setFont(HELVETICA_12);

    graphic2D.setColorRGB(r, g, b);

    const int xWindDirection = 15;
    const int xWindForce = 160;
    const int yWindDirection = 20;
    const int yWindForce = 20;
    const int textSpace = 20;

    // [1] Draw wind direction
    {
	graphic2D.drawText(xWindDirection, yWindDirection, "Wind direction:");
    }

    std::string windDirections[4] = {
	"Key U : north",
	"Key H : west",
	"Key K : east",
	"Key J : south"
    };

    for (int i = 0; i < 4; i++) {
        graphic2D.drawText(xWindDirection, yWindDirection + (textSpace * (i + 1)), windDirections[i]);
    }

    // [2] Draw wind force
    {
	graphic2D.drawText(xWindForce, yWindForce, "Wind force:");
    }

    std::string windForces[2] = {
	"Arrow up : increase force",
	"Arrow bottom : decrease force"
    };

    for (int i = 0; i < 2; i++) {
        graphic2D.drawText(xWindForce, yWindForce + (textSpace * (i + 1)), windForces[i]);
    }
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void ImageCustomEvent::listener(HeaterPoint* heatersQueue , int* windStrength , WindDirection* windDirection)
    {
    this->ptrKeyListener = new SimpleKeyListener(windStrength, windDirection);
    this->ptrMouseListener = new SimpleMouseListener(heatersQueue);

    setKeyListener(ptrKeyListener);
    setMouseListener(ptrMouseListener);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

