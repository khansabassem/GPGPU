#include "SliceGmHostUse.h"

#include "SliceGMHOST.h"
#include "SliceNumber.h"

#include "Maths.h"
#include "Hardware.h"

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

SliceGmHostUse::SliceGmHostUse(const Grid& grid , bool isVerbose) : //
	grid(grid), //
	nbSlice(SliceNumber::nbSlice()), //
	piHat(-1)
    {
    this->ptrRunnableGPU = new SliceGMHOST(grid, this->nbSlice, &piHat, isVerbose);

    assert(filter(grid));
    }

SliceGmHostUse::SliceGmHostUse(bool isVerbose) : //
	SliceGmHostUse(createGrid(), isVerbose)
    {
    //rien
    }

SliceGmHostUse::~SliceGmHostUse()
    {
    delete ptrRunnableGPU;
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/**
 * override
 */
bool SliceGmHostUse::filter(const Grid& grid)
    {
    return Use_I::filter(grid);
    }

/*--------------*\
|*	isOk	*|
 \*-------------*/

/**
 * Override
 */
bool SliceGmHostUse::isOk(bool isVerbose)
    {
    this->ptrRunnableGPU->run();

    bool isOk = Maths::isEquals(piHat, PI, 1e-2); // Si certains de vos tests unitaires manquent de precision, passer a 1e-2 (non associtaivite de l'addition)

    if (isVerbose)
	{
	string title = "[" + ptrRunnableGPU->getTitle() + "]";
	cout << setprecision(4);
	cout << endl;
	cout << title << " : PI hat = " << piHat << endl;
	cout << title << " : PI     = " << PI << endl;
	cout << title << " : ";

	if (isOk)
	    {
	    cout << "Success!" << endl;
	    }
	else
	    {
	    cerr << "Failed!" << endl;
	    }
	}
    return isOk;
    }

/*--------------*\
|*	get	*|
 \*-------------*/

/**
 * override
 * Warning : It's a getter, the user is not responsible for deleting RunnableGPU_I*
 */
RunnableGPU_I* SliceGmHostUse::getRunnableGPU()
    {
    return this->ptrRunnableGPU;
    }

/*--------------------------------------*\
|*		Private			*|
 \*-------------------------------------*/

/**
 * static
 */
Grid SliceGmHostUse::createGrid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP, 1, 1);
    dim3 db(256, 1, 1);
    Grid grid(dg, db);
    return grid;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
