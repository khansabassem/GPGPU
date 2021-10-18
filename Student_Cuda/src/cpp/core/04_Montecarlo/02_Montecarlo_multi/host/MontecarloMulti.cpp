#include "MontecarloMulti.h"

#include <iostream>
#include <assert.h>

#include "Montecarlo.h"
#include "Hardware.h"

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/**
 * static
 */
int MontecarloMulti::NB_DEVICE = Hardware::getDeviceCount();

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

MontecarloMulti::MontecarloMulti(const Grid& grid , entier nbDarTotalAsk , double* ptrPiHat , float h , bool isVerbose) :
	RunnableGPU(grid, title(nbDarTotalAsk, h), isVerbose), // classe parente
//
	nbDarTotalAsk(nbDarTotalAsk), //
	ptrPiHat(ptrPiHat), //
	h(h), //
	grid(grid)
    {
    this->nbDarByDevice = nbDarTotalAsk / NB_DEVICE;
    assert(nbDarByDevice >= grid.threadCounts());

    // warning
	{
	// Charger les drivers de tous les gpus avec:
	//
	//Hardware::loadCudaDriverAll();
	//
	// sinon votre code multi gpu sera sequentiel!
	// Le mieux est de faire ca dans main.cpp avec la directive
	//
	// 	DeviceDriver::LOAD_ALL;
	}
    //tabPtrMontecarlo = new Montecarlo*[3];
    //for(int i = 0; i< NB_DEVICE;i++){
    //    tabPtrMontecarlo[i] = new Montecarlo(grid , nbDarByDevice , ptrPiHat , h , isVerbose);
    //}

    }

MontecarloMulti::~MontecarloMulti()
    {

    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void MontecarloMulti::run()
    {
    const int PREVIOUS_DEVICE_ID = Hardware::getDeviceId();

    this->nbDarTotalEffective = 0;
    entier nbDarUnderCurve = 0;

#pragma omp parallel for
    for (int deviceID = 0; deviceID < NB_DEVICE; ++deviceID)
	{
	Hardware::setDevice(deviceID);
	Montecarlo mt(grid, nbDarByDevice, ptrPiHat, h, isVerbose);
	mt.run();
	entier ndci = mt.getNbDarUnderCurve();
	entier ndei = mt.getNbDarTotalEffective();
	//
	//   (P2) Utiliser une section critique! C'est pas cher, pas beaucoup de GPU, pas beaucoup de threads host-side!
	//
#pragma omp critical(addDevice)
	    {
	    nbDarUnderCurve += ndci;
	    nbDarTotalEffective += ndei;
	    }
	}

    // calculer piHat avec nbDarTotalEffective et nbDarUnderCurve
    *ptrPiHat = nbDarUnderCurve / (double)nbDarTotalEffective * h;

    Hardware::setDevice(PREVIOUS_DEVICE_ID);

    // Tip
    //
    // 		Faite foontionner ce code multiGPU d'abord "sequentiel", Device after Device, puis seulement ensuite tous les GPU en paralell
    // 		Utiliser en ligne de commande
    //
    //			nvidia-smi --loop=1
    //
    // 		pour voir le 100% d'utilisation du device, changer de device en device dans le cas sequentiel, puis voir un 100% simultaner sur tous les devices en meme temps
    // 		Tirer assez de flechette (cas long) pour avoir le temps de monitorer (cf entier.h du to Montecarlo).
    //
    // 		Une fois l'observation terminer, kitter nvidia-smi (CTRL-C)
    //
    // Performance:
    //
    // 		Si les performances en int ne sont pas meilleur, voire moins bonne en multiGPU, vous vous etes surement fait pieger dans la boucle!
    //
    //		Indication :
    //
    //			(I1) Il faut une boucle for dans le contructeur, pour construire les Montecarlo (mono) (et les ranger dans l'attribut tabPtrMontecarlo)
    //			(I2) Il faut une boucle for dans le destructeur, pour detuire les Montecarlo (mono)
    //			(I3) Il faut une boucle for dans le run, pour runner le montecarlo (mono)
    //
    //		Warning:
    //
    // 			(W1) Chaque fois ces boucles doivent etre parallel, et commencer par
    //
    //					Hardware::setDevice(deviceID);
    //
    // 			      y compris dans le destructeur !!
    //
    //			(W2) Oublier pas le coup du Hardware::setDevice(PREVIOUS_DEVICE_ID);
    }

/*----------------*\
 |*	get        *|
 \*---------------*/

entier MontecarloMulti::getNbDarTotalEffective()
    {
    return nbDarTotalEffective;
    }

double MontecarloMulti::getInputGO()
    {
    return (nbDarTotalEffective / (double)1024 / (double)1024 / (double)1024) * sizeof(float) * 2;
    }

/*----------------*\
 |*	set        *|
 \*---------------*/

void MontecarloMulti::setH(float h)
    {
    this->h = h;
    }

/*----------------*\
 |*  private       *|
 \*---------------*/

string MontecarloMulti::title(entier nbDarTotalAsk , float h)
    {
    return "MontecarloMulti-" + entierToString() + "-" + to_string(nbDarTotalAsk) + "-h" + to_string((int)h);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
