#pragma once

#include <curand_kernel.h>

#include "cudas.h"
#include "Grid.h"
#include "entier.h"
#include "RunnableGPU.h"

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * On passse la grille à Montecarlo pour pouvoir facilement la faire varier de l'extérieur pour trouver l'optimum, ou faire des tests avec des grilles différentes
 */
class Montecarlo: public RunnableGPU
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	/**
	 * Hyp : db power 2
	 */
	Montecarlo(const Grid& grid , entier nbDarTotalAsk , double* ptrPiHat , float h , bool isVerbose);

	virtual ~Montecarlo(void);

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
	 * #dar effectivement tirer, !=nbDarTotalAsk car division entiere
	 */
	entier getNbDarTotalEffective();

	entier getNbDarUnderCurve();


    private:

	static std::string title(entier nbDarTotalAsk , float h);

	/*--------------------------------------*\
	|*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	entier nbDarTotalAsk;
	float h; // hauteur de la cible

	// Inputs/Outputs
	double* ptrPiHat;

	// Outputs
	entier nbDarTotalEffective;
	entier nbDarUnderCurve;

	// Tools
	entier* ptrNbDarUnderGM;
	size_t sizeNbDarUnderGM;
	size_t sizeSM;

	curandState* tabDevGeneratorGM;

	entier nbDarByThread;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
