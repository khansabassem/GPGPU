#include "ReductionAddIntI.h"

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

extern __global__ void KAddIntProtocoleI(int* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionAddIntI::ReductionAddIntI(const Grid& grid , int* ptrSum , bool isVerbose) :
	RunnableGPU(grid, "ReductionAddIntI-" + to_string(grid.threadCounts()), isVerbose), // classe parente
	ptrSum(ptrSum)
    {
    // Memory mgmt GM
    GM::mallocInt(&ptrSumGM, 0); // % car le pointeur ne valait rien avant, ca valeur va changer
    this->sizeSM = grid.threadByBlock() * sizeof(int);
    }

ReductionAddIntI::~ReductionAddIntI()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionAddIntI::run()
    {
    // TODO ReductionAddIntI
    KAddIntProtocoleI<<<dg,db,sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_int(ptrSum, ptrSumGM);
    // appeler le kernel
    // recuperer le resulat coter host
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
