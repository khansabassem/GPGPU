#include <iostream>
#include <stdlib.h>

#include "Matlab.h"
#include "Hardware.h"
#include "BruteForce.h"
#include "ProviderUse_I.h"

//AddVector
#include "AddVectorProviderBig.h"

//Slice
#include "SliceProviderGMHOST.h"
#include "SliceProviderGM.h"
#include "SliceProviderSM.h"

//Montecarlo
#include "MontecarloProvider.h"
#include "MontecarloProviderMulti.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void addvectorBig(Matlab* ptrMatlab);

static void sliceGMHOST(Matlab* ptrMatlab);
static void sliceGM(Matlab* ptrMatlab);
static void sliceSM(Matlab* ptrMatlab);

static void montecarlo(Matlab* ptrMatlab);
static void montecarloMulti(Matlab* ptrMatlab);

// Tools
static void bruteforce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS);
static void bruteforceReduction(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBrutforce()
    {
    cout << "\n[Bruteforce] mode" << endl;

    Matlab matlab;

    // one at a time!

//    addvectorBig(&matlab);
    sliceGMHOST(&matlab);
//    sliceGM(&matlab);
//    sliceSM(&matlab);
 //   montecarlo(&matlab);
    // montecarloMulti(&matlab);

    matlab.play();

    cout << "\n[BruteForce] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void addvectorBig(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    AddVectorProviderBig addVectorProviderBig;

    bruteforce(&addVectorProviderBig, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void sliceGMHOST(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    SliceProviderGMHOST sliceProviderGMHOST;

    bruteforce(&sliceProviderGMHOST, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void sliceGM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    SliceProviderGM sliceProviderGM;

    // brutefore: cas special dg et db power 2
	{
	const int WARP_SIZE = Hardware::getWarpSize();

	// dg
	Iterator iteratorDGx(WARP_SIZE, 1024, 2, Operator::MULTIPLY); // (min,max,step) // power 2

	// db
	Iterator iteratorDBx(WARP_SIZE, 1024, 2, Operator::MULTIPLY); // (min,max,step) // power 2

	// gridMaillage
	GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

	BruteForce::run(&sliceProviderGM, &gridMaillage, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
	}
    }

void sliceSM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    SliceProviderSM sliceProviderSM;

    bruteforceReduction(&sliceProviderSM, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void montecarlo(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    MontecarloProvider montecarloProvider;

    bruteforceReduction(&montecarloProvider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void montecarloMulti(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9;
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    MontecarloProviderMulti montecarloProviderMulti;

    bruteforceReduction(&montecarloProviderMulti, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

/**
 * db power2
 */
void bruteforceReduction(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS)
    {
    // Hardware
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    const int NB_THREAD_BLOCK_MAX = Hardware::getMaxThreadPerBlock();
    const int WARP_SIZE = Hardware::getWarpSize();

    // dg
    Iterator iteratorDGx(MP, 10 * MP, MP, Operator::ADD); // (min,max,step)

    // db
    //  Iterator iteratorDBx(WARP_SIZE, NB_THREAD_BLOCK_MAX, 2, Operator::MULTIPLY); // power2 (reduction)
    Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, 2, Operator::MULTIPLY); // power2 (reduction)

    // gridMaillage
    GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

    BruteForce::run(ptrProviderUse, &gridMaillage, ptrMatlab, plotType, durationMaxS);
    }


void bruteforce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS)
    {
    // Hardware
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    const int NB_THREAD_BLOCK_MAX = Hardware::getMaxThreadPerBlock();
    const int WARP_SIZE = Hardware::getWarpSize();

    // dg
    Iterator iteratorDGx(MP, 10 * MP, MP, Operator::ADD); // (min,max,step)

    // db
    Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, CORE_MP, Operator::ADD); // (min,max,step)

    // gridMaillage
    GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

    BruteForce::run(ptrProviderUse, &gridMaillage, ptrMatlab, plotType, durationMaxS);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

