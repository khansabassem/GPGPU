#include "ReductionIntI.h"

#include "GM.h"
#include "Grid.h"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void KIntProtocoleI(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionIntI::ReductionIntI(const Grid& grid , int* ptrSum , bool isVerbose) :
	RunnableGPU(grid, "ReductionIntI-" + to_string(grid.threadCounts()), isVerbose), // classe parente
	ptrSum(ptrSum)
    {
    GM::mallocInt(&ptrSumGM, 0); // % car le pointeur ne valait rien avant, ca valeur va changer
    this->sizeSM = grid.threadByBlock() * sizeof(int);
    }

ReductionIntI::~ReductionIntI()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionIntI::run()
    {
    KIntProtocoleI<<<dg,db,sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_int(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
