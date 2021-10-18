#include <iostream>
#include <stdlib.h>

#include "Iterator.h"
#include "BruteForce.h"
#include "Hardware.h"

#include "core/05_Project_HeatTransfer/provider/HeatTransferProviderGM.h"
#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "RaytracingProviderGM.h"
#include "RaytracingProviderSM.h"
#include "RaytracingProviderCM.h"
#include "RaytracingProviderCM2SM.h"
#include "NewtonProvider.h"

// Project

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

static void rippling(Matlab* ptrMatlab);
static void mandelbrot(Matlab* ptrMatlab);
static void raytracingGM(Matlab* ptrMatlab);
static void raytracingCM(Matlab* ptrMatlab);
static void raytracingSM(Matlab* ptrMatlab);
static void raytracingCM2SM(Matlab* ptrMatlab);
static void newton(Matlab* ptrMatlab);
static void heatTransfer(Matlab* ptrMatlab);


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

    // Please, un a la fois!
//         rippling(&matlab);
   //mandelbrot(&matlab); // Conseil : use nFixe (by example nMin=nMax=100)
//    raytracingGM(&matlab);
   // raytracingCM(&matlab);
  //  raytracingSM(&matlab);
//    raytracingCM2SM(&matlab);
   //    newton(&matlab);
    heatTransfer(&matlab);


    matlab.play();

    cout << "\n[BruteForce] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.01; // 0.9 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RipplingProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }
void newton(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.01; // 0.9 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RipplingProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void mandelbrot(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.4; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    MandelbrotProvider provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void raytracingGM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RaytracingProviderGM provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void raytracingSM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RaytracingProviderSM provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void raytracingCM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RaytracingProviderCM provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void raytracingCM2SM(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9; // 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    RaytracingProviderCM2SM provider;
    bruteForce<uchar4>((ProviderUse_I*)&provider, ptrMatlab, PLOT_TYPE, DURATION_MAX_S);
    }

void heatTransfer(Matlab* ptrMatlab)
    {
    const double DURATION_MAX_S = 0.9; // 0.9 1 grid
    const PlotType PLOT_TYPE = PlotType::ALL_GRAPHE;

    HeatTransferProviderGM provider;
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
    // Iterator iteratorDBx(WARP_SIZE, NB_THREAD_BLOCK_MAX, WARP_SIZE, Operator::ADD);
    // Iterator iteratorDBx(CORE_MP, NB_THREAD_BLOCK_MAX, 2, Operator::MULTIPLY); // power2 (reduction)

    // gridMaillage
    GridMaillage gridMaillage(iteratorDGx, iteratorDBx);

    BruteForce::run(ptrProviderUse, &gridMaillage, ptrMatlab, plotType, durationMaxS);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
