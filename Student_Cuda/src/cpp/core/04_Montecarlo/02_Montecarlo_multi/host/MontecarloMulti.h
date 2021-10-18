#pragma once

#include <curand_kernel.h>

#include "cudas.h"
#include "Grid.h"
#include "entier.h"
#include "RunnableGPU.h"
#include "Montecarlo.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * On passse la grille à MontecarloMulti pour pouvoir facilement la faire varier de l'extérieur pour trouver l'optimum, ou faire des tests avec des grilles différentes
 */
class MontecarloMulti: public RunnableGPU
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * update piHat
	 * Hyp : nbThread est une puissance de 2
	 */
	MontecarloMulti(const Grid& grid , entier nbDarTotalAsk , double* ptrPiHat , float h , bool isVerbose);

	virtual ~MontecarloMulti(void);

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
	virtual double getInputGO();

	/**
	 * #dar effectivement tirer
	 */
	entier getNbDarTotalEffective();

	void setH(float h);

    private:

	std::string title(entier nbDarTotalAsk , float h);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	entier nbDarTotalAsk;
	float h;

	// Inputs/Outputs
	double* ptrPiHat;

	// Tools
	entier nbDarTotalEffective;

	entier nbDarByDevice;
	Grid grid;

	Montecarlo** tabPtrMontecarlo;

	static int NB_DEVICE;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
