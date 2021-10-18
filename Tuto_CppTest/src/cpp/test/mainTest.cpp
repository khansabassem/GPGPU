#include <stdlib.h>
#include <fstream>
#include <string>

#include "TestCalculatriceFloat.h"
#include "TestCalculatriceInt.h"
#include "CppTest.h"


using std::cout;
using std::endl;
using std::string;
using std::ofstream;
using std::auto_ptr;

using Test::Suite;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static int testUnique(OutputType outputType);

static int testSuite(OutputType outputType);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

int mainTest(void)
    {
    cout << "mainTest" << endl;

    // unique
	{
//	return testUnique(OutputType::HTML);
//	return testUnique(OutputType::CONSOLE);
	}

    // suite
	{
	return testSuite(OutputType::HTML);
	//return testSuite(OutputType::CONSOLE);
	}
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

int testUnique(OutputType outputType)
    {
    TestCalculatriceInt testCaluclatriceInt;

    // run
	{
	string folder = "./out";
	string title = "testTutoTest";
	string fileHTML = title + ".html";

	//Folders::mkdirP(folder);

	int result = CppTest::run(folder, fileHTML, title, testCaluclatriceInt, outputType); // HTML CONSOLE

	//Chrome::showHTML(folder, fileHTML);

	return result;
	}
    }

int testSuite(OutputType outputType)
    {
    Suite testSuite;

    testSuite.add(auto_ptr < Suite > (new TestCalculatriceFloat()));
    testSuite.add(auto_ptr < Suite > (new TestCalculatriceInt()));

    // run
	{
	string folder = "./out";
	string title = "testAll";
	string fileHTML = title + ".html";

	//Folders::mkdirP(folder);

	int result = CppTest::run(folder, fileHTML, title, testSuite, outputType); // HTML CONSOLE

	//Chrome::showHTML(folder, fileHTML);

	return result;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

