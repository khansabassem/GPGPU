#include <iostream>
#include <stdlib.h>

#include "Iterator.h"
#include "BruteForce.h"
#include "Hardware.h"

#include "ImageVideoProvider.h"

using std::cerr;
using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |* Declaration *|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void imageVideo(Matlab* ptrMatlab);

//tools
template<typename T>
static void bruteForce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS = 0.5);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBrutforce()
    {
    cout << "\n[BruteForce] mode" << endl;

    Matlab matlab;

    // Attention : Un a la fois seulement!

    imageVideo(&matlab);

    matlab.play();

    cout << "\n[BruteForce] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void imageVideo(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.5; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    ImageVideoProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

/*--------------------------------------*\
 |*		Tools			*|
 \*-------------------------------------*/

template<typename T>
void bruteForce(ProviderUse_I* ptrProviderUse , Matlab* ptrMatlab , const PlotType& plotType , double durationMaxS)
    {
// Hardware
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();
    const int NB_THREAD_BLOCK_MAX = Hardware::getMaxThreadPerBlock();
    const int WARP_SIZE = Hardware::getWarpSize();

// dg
    Iterator iteratorDGx(MP, 10 * MP, MP, Operator::ADD); // (min,max,step)

// db
    Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, CORE_MP, Operator::ADD);
// Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, WARP_SIZE, Operator::ADD);
// Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, 2, Operator::MULTIPLY); // power2 (reduction)

// gridMaillage
    GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

    BruteForce::run(ptrProviderUse, &gridMaillage, ptrMatlab, plotType, durationMaxS);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
