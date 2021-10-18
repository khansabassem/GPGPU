#include <stdlib.h>
#include <iostream>
#include <string>
#include <iomanip>

#include "CppTest.h"
#include "cudas.h"
#include "Folders.h"
#include "Chrome.h"

#include "TestVector.h"

// Slice
#include "TestSliceGMHOST.h"
#include "TestSliceGM.h"
#include "TestSliceSM.h"

// Montecarlo
#include "TestMontecarlo.h"
#include "TestMontecarloMulti.h"

using std::string;
using std::cout;
using std::endl;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest()
    {
    Suite testSuite;

    // AddVector
	{
	//testSuite.add(std::auto_ptr < Suite > (new TestVector()));
	}

    // Slice
	{
	testSuite.add(std::auto_ptr < Suite > (new TestSliceGMHOST()));
	testSuite.add(std::auto_ptr < Suite > (new TestSliceGM()));
	testSuite.add(std::auto_ptr < Suite > (new TestSliceSM()));
	}

// Montecarlo
	{
	for (float h = 4; h <= 7; h = h + 1)
	    {
	    testSuite.add(std::auto_ptr < Suite > (new TestMontecarlo(h)));
	    }
//
	for (float h = 4; h <= 7; h = h + 1)
	    {
	    testSuite.add(std::auto_ptr < Suite > (new TestMontecarloMulti(h)));
	    }
	}

// run
	{
	string folder = "./out";
	string title = "testAll"; // see above, title list
	string fileHTML = title + ".html";

	Folders::mkdirP(folder);

	int result = CppTest::run(folder, fileHTML, title, testSuite, OutputType::HTML); // HTML CONSOLE

	Chrome::showHTML(folder, fileHTML); // to be commented if OutputType::CONSOLE

	return result;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

