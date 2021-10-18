#pragma once

#include "cudas.h"
#include "Grid.h"
#include "Pattern.h"
#include "RunnableGPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * On passse la grille à AddVector pour pouvoir facilement la faire varier de l'extérieur pour trouver l'optimum, ou faire des tests avec des grilles différentes
 */
class AddVector: public RunnableGPU
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * update w by v1+v2
	 */
	AddVector(const Grid& grid , float* ptrV1 , float* ptrV2 , float* ptrW , int n , Pattern pattern, bool isVerbose);

	virtual ~AddVector(void);

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * override
	 */
	virtual void run();

	/**
	 * override
	 */
	virtual double getOutputGO();

	/**
	 * override
	 */
	virtual double getInputGO();

    private:

	std::string title();

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	float* ptrV1;
	float* ptrV2;
	int n;
	Pattern pattern;

	// Inputs/Outputs
	float* ptrW;

	// Tools
	float* ptrDevV1;
	float* ptrDevV2;
	float* ptrDevW;
	size_t sizeVector; //[octet] permet de faire du memory management

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
