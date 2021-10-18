#pragma once

#include "cudas.h"
#include "Maths.h"
#include "Animable_I_GPU.h"
#include "HeaterPoint.h"
#include "WindDirection.h"
#include <list>
using namespace gpu;

#include "heatReal.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class HeatTransfer: public Animable_I<uchar4>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	HeatTransfer(const Grid& grid , uint w , uint h , float dt , bool isVerbose , HeaterPoint* ptrHeatersQueue , int* ptrWindStrength ,
		WindDirection* windDirection);
	virtual ~HeatTransfer(void);

	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

	HeaterPoint* getHeaterQueue();

	int* getWindStrength();
	WindDirection* getWindDirection();

    private:

	void manageMemory(size_t size);
	void initializeImages();
	void copyImage(size_t size);
	void listener(void);

	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	float dt;
	int w;
	int h;

	int NB_ITERATION_AVEUGLE;
	int currentIterationNumber;

	// images
	real* imageHeater;
	real* imageInit;
	real* ptrDevImageInit;
	real* ptrDevImageHeater;
	real* ptrDevImageA;
	real* ptrDevImageB;

	int* windStrength;
	WindDirection* windDirection;

	// Heaters
	HeaterPoint* heaterPointQueue;
    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
