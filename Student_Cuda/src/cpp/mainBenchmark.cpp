#include <iostream>
#include <stdlib.h>

#include "Benchmark.h"

#include "AddVectorBigUse.h"

// Slice
#include "SliceGmHostUse.h"
#include "SliceGmUse.h"
#include "SliceSmUse.h"

// Montecarlo
#include "MontecarloUse.h"
#include "MontecarloMultiUse.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void addvector();
static void sliceGMHOST();
static void sliceGM();
static void sliceSM();
static void montecarlo();
static void montecarloMulti();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainBenchmark()
    {
    cout << "\n[Benchmark] mode" << endl;

    // one at a time!
   // addvector();
//    sliceGMHOST();
//    sliceGM();
   // sliceSM();
    montecarlo();
//    montecarloMulti();

    cout << "\n[Benchmark] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void addvector()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    AddVectorBigUse addVectorUse(IS_VERBOSE);

    Benchmark::run(addVectorUse.getRunnableGPU(), DURATION_MAX_S);
    }

void sliceGMHOST()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    SliceGmHostUse sliceGmHostUse(IS_VERBOSE);

    Benchmark::run(sliceGmHostUse.getRunnableGPU(), DURATION_MAX_S);
    }

void sliceGM()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    SliceGmUse sliceGmUse(IS_VERBOSE);

    Benchmark::run(sliceGmUse.getRunnableGPU(), DURATION_MAX_S);
    }

void sliceSM()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    SliceSmUse sliceSmUse(IS_VERBOSE);

    Benchmark::run(sliceSmUse.getRunnableGPU(), DURATION_MAX_S);
    }

void montecarlo()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    MontecarloUse montecarloUse(IS_VERBOSE);

    Benchmark::run(montecarloUse.getRunnableGPU(), DURATION_MAX_S);
    }

void montecarloMulti()
    {
    const double DURATION_MAX_S = 10;
    const bool IS_VERBOSE = false;

    MontecarloMultiUse montecarloMultiUse(IS_VERBOSE);

    Benchmark::run(montecarloMultiUse.getRunnableGPU(), DURATION_MAX_S);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

