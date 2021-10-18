#include "HeatTransfer.h"
#include "GM.h"
#include "HM.h"
#include <iostream>
#include <assert.h>
#include "Hardware.h"
#include "HeaterPoint.h"
#include "WindDirection.h"
#include <list>
using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void heatTransferDiffusion(real* ptrImgInputOutput, real* ptrImgHeater, int w, int h,
	int cardinalCoefficientNS, int cardinalCoefficientWE);
extern __global__ void heatTransferEcrasement(real* ptrImgInput, real* ptrImgOutput, int w, int h);
extern __global__ void heatTransferToScreenImageHSB(uchar4* ptrDevPixels, real* ptrImgInput, int w, int h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

HeatTransfer::HeatTransfer(const Grid& grid , uint w , uint h , float dt , bool isVerbose , HeaterPoint* ptrHeatersQueue , int* ptrWindStrength ,
	WindDirection* ptrWindDirection) :
	Animable_I<uchar4>(grid, w, h, "HeatTransfer-Cuda-uchar4", isVerbose) // super classe
    {
    this->w = w;
    this->h = h;

    // Animation
    this->dt = dt;
    this->t = 0; // protected dans Animable
    this->NB_ITERATION_AVEUGLE = 50;
    this->currentIterationNumber = 0;
    this->heaterPointQueue = ptrHeatersQueue;
    this->windStrength = ptrWindStrength;
    this->windDirection = ptrWindDirection;
    size_t size = this->w * this->h * sizeof(real);

    manageMemory(size);
    initializeImages();
    copyImage(size);
    }

HeatTransfer::~HeatTransfer()
    {
    // rien
    }

HeaterPoint* HeatTransfer::getHeaterQueue()
    {
    return this->heaterPointQueue;
    }

int* HeatTransfer::getWindStrength()
    {
    return this->windStrength;
    }

WindDirection* HeatTransfer::getWindDirection()
    {
    return this->windDirection;
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car image pas zoomable
 */
void HeatTransfer::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    real* ptrImageInput = NULL;
    real* ptrImageOutput = NULL;
    if ((this->currentIterationNumber % 2) == 0)
	{
	ptrImageInput = ptrDevImageA;
	ptrImageOutput = ptrDevImageB;
	}
    else
	{
	ptrImageInput = ptrDevImageB;
	ptrImageOutput = ptrDevImageA;
	}

    // Heaters
    if (heaterPointQueue[0].x != 0 || heaterPointQueue[0].y != 0)
	{
	const int pixelToHeat = heaterPointQueue[0].y * this->w + heaterPointQueue[0].x;
	imageHeater[pixelToHeat] = (real)1;

	GM::memcpyHToD(&(ptrDevImageHeater[pixelToHeat]), &(imageHeater[pixelToHeat]), sizeof(real));
	heaterPointQueue[0].x = 0;
	heaterPointQueue[0].y = 0;
	}

    int windStrengthValue = *windStrength;
    /*
     * By default, cardinalCoefficients contains 0 values, where:
     *
     * Index 0 = NORTH
     * Index 1 = EAST
     * Index 2 = SOUTH
     * Index 3 = WEST
     */
    int cardinalCoefficients[2] =
	{
	};
    WindDirection windDirectionValue = *windDirection;
    switch (windDirectionValue)
	{
    case WindDirection::NORTH:
	cardinalCoefficients[0] = windStrengthValue;
	break;
    case WindDirection::EAST:
	cardinalCoefficients[1] = windStrengthValue;
	break;
    case WindDirection::SOUTH:
	cardinalCoefficients[0] = windStrengthValue * -1;
	break;
    case WindDirection::WEST:
	cardinalCoefficients[1] = windStrengthValue * -1;
	break;
    default:
	// nothing to do
	break;
	}

    heatTransferDiffusion<<<dg,db>>>(ptrImageInput, ptrImageOutput, this->w, this->h,
	    cardinalCoefficients[0],
	    cardinalCoefficients[1]);

    heatTransferEcrasement<<<dg,db>>>(ptrImageOutput, ptrDevImageHeater, this->w, this->h);

    //display ??
    if (currentIterationNumber % NB_ITERATION_AVEUGLE == 0)
	{
    heatTransferToScreenImageHSB<<<dg,db>>>(tabPixelsGM, ptrImageOutput, this->w, this->h);
    }

currentIterationNumber++;
}

/**
 * Override
 * Call periodicly by the API
 */
void HeatTransfer::animationStep()
{
t += dt;
}

void HeatTransfer::manageMemory(size_t size)
{
//Global Memory
this->ptrDevImageInit = NULL;
this->ptrDevImageHeater = NULL;
this->ptrDevImageA = NULL;
this->ptrDevImageB = NULL;

GM::malloc(&ptrDevImageInit, size);
GM::malloc(&ptrDevImageHeater, size);
GM::malloc0(&ptrDevImageA, size);
GM::malloc0(&ptrDevImageB, size);
}

void HeatTransfer::copyImage(size_t size)
{
GM::memcpyHToD(ptrDevImageInit, this->imageInit, size);
GM::memcpyHToD(ptrDevImageHeater, this->imageHeater, size);
}

void HeatTransfer::initializeImages()
{
imageHeater = new real[this->w * this->h];
imageInit = new real[this->w * this->h];
}

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

