#include <iostream>
#include <stdlib.h>

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"
#include "RaytracingProviderGM.h"
#include "RaytracingProviderSM.h"
#include "RaytracingProviderCM.h"
#include "RaytracingProviderCM2SM.h"
#include "NewtonProvider.h"

// Project
#include "HeatTransferProviderGM.h"


#include "BenchmarkImage.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void rippling();
static void mandelbrot();
static void raytracingGM();
static void raytracingCM();
static void raytracingSM();
static void raytracingCM2SM();
static void newton();
static void heatTransfer();


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    // Please, un a la fois!
//    rippling();
//    mandelbrot(); // Conseil : use nFixe (by example nMin=nMax=80)
//     raytracingGM();
//    raytracingSM();
//    raytracingCM();
//     raytracingCM2SM();
    // newton();

    heatTransfer();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void rippling()
    {
    const double DURATION_MAX_S = 8;

    RipplingProvider provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }
void newton()
    {
    const double DURATION_MAX_S = 8;

    NewtonProvider provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void mandelbrot()
    {
    const double DURATION_MAX_S = 8;

    MandelbrotProvider provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void raytracingGM()
    {
    const double DURATION_MAX_S = 8;

    RaytracingProviderGM provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void raytracingCM()
    {
    const double DURATION_MAX_S = 8;

    RaytracingProviderCM provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void raytracingSM()
    {
    const double DURATION_MAX_S = 8;

    RaytracingProviderSM provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void raytracingCM2SM()
    {
    const double DURATION_MAX_S = 8;

    RaytracingProviderCM2SM provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

void heatTransfer()
    {
    const double DURATION_MAX_S = 8;

    HeatTransferProviderGM provider;

    BenchmarkImage<uchar4>::run(&provider, DURATION_MAX_S);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

