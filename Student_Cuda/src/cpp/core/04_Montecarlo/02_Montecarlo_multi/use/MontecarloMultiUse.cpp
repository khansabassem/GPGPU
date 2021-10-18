#include "MontecarloMultiUse.h"

#include "MontecarloUseTools.h"
#include "MontecarloMulti.h"

#include "Maths.h"
#include "Hardware.h"
#include "ChronoFactory.h"

#include <iostream>
#include <iomanip>
#include <assert.h>

using std::cerr;
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::setprecision;

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeurs		*|
 \*-------------------------------------*/

/*--------------*\
|*	test*|
 \*-------------*/

MontecarloMultiUse::MontecarloMultiUse(const Grid& grid , bool isVerbose , entier nbDar , float h) : //
	nbDar(nbDar), //
	grid(grid), //
	piHat(-1)
    {
    this->ptrRunnableGPU = new MontecarloMulti(grid, nbDar, &this->piHat, h, isVerbose);
    }

MontecarloMultiUse::MontecarloMultiUse(bool isVerbose , entier nbDar , float h) : //
	MontecarloMultiUse(createGrid(), isVerbose, nbDar, h)
    {
    // rien
    }

/*--------------*\
|*	standard*|
 \*-------------*/

MontecarloMultiUse::MontecarloMultiUse(const Grid& grid , bool isVerbose) : //
	MontecarloMultiUse(grid, isVerbose, MontecarloUseTools::nbDarTotalUse(), MontecarloUseTools::H)
    {
    // rien
    }

MontecarloMultiUse::MontecarloMultiUse(bool isVerbose , float h) : //
	MontecarloMultiUse(createGrid(), isVerbose, MontecarloUseTools::nbDarTotalUse(), h)
    {
    //rien
    }

MontecarloMultiUse::MontecarloMultiUse(bool isVerbose) : //
	MontecarloMultiUse(createGrid(), isVerbose)
    {
    //rien
    }

MontecarloMultiUse::~MontecarloMultiUse()
    {
    delete ptrRunnableGPU;
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/**
 * override
 */
bool MontecarloMultiUse::filter(const Grid& grid)
    {
    return Use_I::filter(grid) //
    && Maths::isPower2(grid.threadByBlock());
    }

/*--------------*\
|*	isOk	*|
 \*-------------*/

bool MontecarloMultiUse::isOk(bool isVerbose)
    {
    bool isOk = true;

    Chrono* ptrChrono = ChronoFactory::create();
    ptrRunnableGPU->run();
    ptrChrono->stop();

    isOk &= Maths::isEquals(this->piHat, PI, 1e-3);

    if (isVerbose)
	{
	string title = "[" + ptrRunnableGPU->getTitle() + "]";
	cout << endl << title;

	MontecarloUseTools::performance(ptrChrono->getElapseTimeS(), nbDar, isOk);
	}

    delete ptrChrono;

    return isOk;
    }

/*--------------*\
|*	get	*|
 \*-------------*/

/**
 * override
 * Warning : It's a getter, the user is not responsible for deleting RunnableGPU_I*
 */
RunnableGPU_I* MontecarloMultiUse::getRunnableGPU()
    {
    return ptrRunnableGPU;
    }

/*--------------------------------------*\
|*		private			*|
 \*-------------------------------------*/

/**
 * static
 */
Grid MontecarloMultiUse::createGrid()
    {
    const int MP = Hardware::getMPCount();

    // Contraintes :
    //	(C1) max(dg.x*dg.y*dg.z)<=1024
    //	(C2) db power 2 (reduction)

#ifdef DAR_INT

    dim3 dg(476, 1, 1);
    dim3 db(64, 1, 1);
    Grid grid(dg, db);

    return grid;
#endif

#ifdef DAR_LONG
    dim3 dg(136,1,1);
    dim3 db(1024,1,1);
    Grid grid(dg, db);

    return grid;
#endif
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
