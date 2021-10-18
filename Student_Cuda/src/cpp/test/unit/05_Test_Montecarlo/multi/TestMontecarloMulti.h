#pragma once

#include "TestCudaPower2.h"
#include "FilterGridMontecarlo.h"
#include "MontecarloUseTools.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class TestMontecarloMulti: public TestCudaPower2
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	TestMontecarloMulti(float h=MontecarloUseTools::H);

	~TestMontecarloMulti();

	/*--------------------------------------*\
	|*		Methode			*|
	 \*-------------------------------------*/

    protected:

	/**
	 * Override
	 */
	void allTests();

    private:

	void testSpecial();

	static long thresholdPerformanceFps();

	/*--------------------------------------*\
	|*		Attribut		*|
	 \*-------------------------------------*/

    private:

	FilterGridMontecarlo* ptrFilterGridMontecarlo;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

