#include <iostream>
#include <stdlib.h>

using std::cerr;
using std::cout;
using std::endl;

#include "Limits.h"
#include "ChronoFactory.h"

// hello
extern void addScalar();
extern bool isAddScalar_Ok();

// Vector
#include "AddVectorSmallUse.h"
#include "AddVector11Use.h"
#include "AddVectorBigUse.h"

// Slice
#include "SliceGmHostUse.h"
#include "SliceGmUse.h"
#include "SliceSmUse.h"

// Montecarlo
#include "MontecarloUse.h"
#include "MontecarloMultiUse.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainUse()
    {
    Chrono* ptrChrono = ChronoFactory::create();

    const int IS_VERBOSE = true;

    // Commenter ce dont vous n'avez pas besoin ci-dessous

    bool isOk = true;

    // Hello
	{
	//addScalar();
	//isOk &= isAddScalar_Ok();
	}

    // Vector
	{
	//AddVectorSmallUse addVectorSmallUse(IS_VERBOSE);
	//AddVector11Use addVector11Use(IS_VERBOSE);
	//AddVectorBigUse addVectorBigUse(IS_VERBOSE);

	//isOk &= addVectorSmallUse.isOk(IS_VERBOSE);
	//isOk &= addVector11Use.isOk(IS_VERBOSE);
	//isOk &= addVectorBigUse.isOk(false);
	}

    // slice
	{
	SliceGmHostUse sliceGmHostUse(IS_VERBOSE);
	//SliceGmUse sliceGmUse(IS_VERBOSE);
	//SliceSmUse sliceSmUse(IS_VERBOSE);
//
//	isOk &= sliceGmHostUse.isOk(IS_VERBOSE);
	//	isOk &= sliceGmUse.isOk(IS_VERBOSE);
	//isOk &= sliceSmUse.isOk(IS_VERBOSE);
	}

    // montecarlo
	{
	/*
	 for (float h = 4; h <= 10; h = h + 1)
	 {
	 //MontecarloUse montecarloUse(IS_VERBOSE, h);
	 //isOk &= montecarloUse.isOk(IS_VERBOSE);
	 }
	 cout << endl;

	 for (float h = 4; h <= 10; h = h + 1)
	 {
	 MontecarloMultiUse montecarloMultiUse(IS_VERBOSE, h);
	 isOk &= montecarloMultiUse.isOk(IS_VERBOSE);
	 }
	 */
	}

    ptrChrono->stop();

    cout << endl << endl;
    cout << "mainCore :" << *ptrChrono << endl;
    cout << "mainCore : ";
    if (isOk)
	{
	cout << "SUCCESS, Congratulation!";
	}
    else
	{
	cerr << "FAILED, sorry!";
	}
    cout << endl << endl;

    delete ptrChrono;

    return isOk ? EXIT_SUCCESS : EXIT_FAILURE;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

