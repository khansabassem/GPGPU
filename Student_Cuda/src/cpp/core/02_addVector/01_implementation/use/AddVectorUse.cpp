#include "AddVectorUse.h"

#include "VectorTools.h"
#include "AddVector.h"
#include "Limits.h"

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


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Constructor		*|
 \*-------------------------------------*/

AddVectorUse::AddVectorUse(const Grid& grid , int n , Pattern pattern,bool isVerbose) : //
	grid(grid), //
	n(n), //
	pattern(pattern)
    {
    assert(filter(grid));

    this->ptrV1 = VectorTools::createV1(n);
    this->ptrV2 = VectorTools::createV2(n);
    this->ptrW = VectorTools::create(n);

    this->ptrRunnableGPU = new AddVector(grid, ptrV1, ptrV2, ptrW, n, pattern,isVerbose);
    }

AddVectorUse::~AddVectorUse()
    {
    delete ptrRunnableGPU; // warning : si destructeur pas virtuel dans classe parente de AddVector, ko, car appel destructeur super classe only!
    //delete ((AddVector*)ptrRunnableGPU); // plus safe!

    VectorTools::free(ptrV1);
    VectorTools::free(ptrV2);
    VectorTools::free(ptrW);
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/**
 * override
 */
bool AddVectorUse::filter(const Grid& grid)
    {
    return Use_I::filter(grid);
    }

int AddVectorUse::getN()
    {
    return n;
    }

/*--------------------------------------*\
|*		isOk			*|
 \*-------------------------------------*/

bool AddVectorUse::isOk(bool isVerbose)
    {
    this->ptrRunnableGPU->run();

    bool isOk = VectorTools::isAddVector_Ok(ptrV1, ptrV2, ptrW, n);

    if (isVerbose)
	{
	VectorTools::print(ptrV1, n);
	VectorTools::print(ptrV2, n);
	cout << "--------------------------------------------------------------------" << endl;
	VectorTools::print(ptrW, n);
	cout << endl;

	cout << "[" << ptrRunnableGPU->getTitle() << "] : ";

	if (isOk)
	    {
	    cout << "Success!" << endl << endl;
	    }
	else
	    {
	    cerr << "Failed!" << endl << endl;
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
RunnableGPU_I* AddVectorUse::getRunnableGPU()
    {
    return this->ptrRunnableGPU;
    }

/*--------------------------------------*\
|*		Private			*|
 \*-------------------------------------*/

/**
 * static
 */
Grid AddVectorUse::createGrid()
    {
    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();


    dim3 dg(25,20,1);
    dim3 db(10,10,1);
    Grid grid(dg,db);

    return grid;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
