#include <iostream>
#include <stdlib.h>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

using std::cout;
using std::endl;

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern bool useOption(int argc, char** argv);

extern bool useThread(void);
extern bool useSynchronization(void);
extern bool useFifoBoostSynchro(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool mainBoost(int argc, char** argv);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static bool mainBoost();

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool mainBoost(int argc, char** argv)
    {
    bool isOk = true;

    isOk &= useOption(argc, argv);
    isOk &= mainBoost();

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

bool mainBoost()
    {
    bool isOk = true;

    isOk &= useThread();
    isOk &= useSynchronization();
    isOk &= useFifoBoostSynchro();

    return isOk;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

