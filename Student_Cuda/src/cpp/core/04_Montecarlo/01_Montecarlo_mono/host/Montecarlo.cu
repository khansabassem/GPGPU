#include "Montecarlo.h"

#include <iostream>
#include <assert.h>
#include <typeinfo>
#include <math.h>

#include "GM.h"
#include "Hardware.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void createGenerator(curandState* tabGeneratorGM,int deviceId);

extern __global__ void montecarlo(curandState* tabGeneratorGM, entier nbDarByThread, entier* ptrNbDarUnderGM, float h);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

Montecarlo::Montecarlo(const Grid& grid , entier nbDarTotalAsk , double* ptrPiHat , float h , bool isVerbose) :
	RunnableGPU(grid, title(nbDarTotalAsk, h), isVerbose), // classe parente
	//
	nbDarTotalAsk(nbDarTotalAsk), //
	ptrPiHat(ptrPiHat), //
	h(h) //

    {
    const entier NB_THREAD = grid.threadCounts(); //directement en entier pour éviter un cast

    // Math : Calculer le nombre de flechette effectivment tirees!
	{
	this->nbDarByThread = nbDarTotalAsk / NB_THREAD;
	this->nbDarTotalEffective = nbDarByThread * NB_THREAD;// TODO Montecarlo

	assert(nbDarTotalAsk >= grid.threadCounts());
	assert(nbDarByThread > 0); // si =0, trop de threads et pas assez de dar!
	}

    // MM
	{
	this->sizeNbDarUnderGM = sizeof(entier); // [octet]

	// Montecarlo MM NbDarUnderGM (pas oublier de mettre a zero, avec un malloc0 par exemple)
	GM::malloc0(&ptrNbDarUnderGM, sizeNbDarUnderGM);

	this->sizeSM = sizeof(entier) * grid.threadByBlock(); // [octet]
	}

    // init : lancer le kernel de creation des generators
	{
	size_t sizeTabDevGeneratorGM = NB_THREAD * sizeof(curandState);

	// TODO Montecarlo MM pou  tabDevGeneratorGM
	 GM::malloc(&tabDevGeneratorGM, sizeTabDevGeneratorGM);
	// TODO Montecarlo lancer le kernel createGenerator
	int deviceId = Hardware::getDeviceId();
	createGenerator<<<dg, db>>>(tabDevGeneratorGM, deviceId);

	}
    }

Montecarlo::~Montecarlo(void)
    {
//MM (device free)
	{
	GM::free(tabDevGeneratorGM);
	GM::free(ptrNbDarUnderGM);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Lancer kernel
 * Recuperer resultat coter host
 * Finaliser le calcul de pi
 */
void Montecarlo::run()
    {
    montecarlo<<<dg, db, sizeSM>>>(tabDevGeneratorGM , nbDarByThread , ptrNbDarUnderGM , h);
    GM::memcpyDToH(&nbDarUnderCurve, ptrNbDarUnderGM, sizeNbDarUnderGM);
    *ptrPiHat = nbDarUnderCurve/(double)nbDarTotalEffective * h; /// (double)nbDarTotalEffective;
    }

/*----------------*\
 |*	get        *|
 \*---------------*/

entier Montecarlo::getNbDarTotalEffective()
    {
    return nbDarTotalEffective;
    }

entier Montecarlo::getNbDarUnderCurve()
    {
    return nbDarUnderCurve;
    }

double Montecarlo::getInputGO()
    {
    return (nbDarTotalEffective / (double)1024 / (double)1024 / (double)1024) * sizeof(float) * 2;
    }

/*----------------*\
 |*  private       *|
 \*---------------*/

/**
 * static
 */
string Montecarlo::title(entier nbDarTotalAsk , float h)
    {
    return "Montecarlo-" + entierToString() + "-" + to_string(nbDarTotalAsk) + "-h" + to_string((int)h);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
