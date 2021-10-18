#include "ReductionLongII.h"

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

extern __global__ void KLongProtocoleII(long* ptrSumGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

ReductionLongII::ReductionLongII(const Grid& grid , long* ptrSum , bool isVerbose) :
	RunnableGPU(grid, "ReductionLongII-" + to_string(grid.threadCounts()), isVerbose), // classe parente
	ptrSum(ptrSum)
    {
    GM::mallocLong(&ptrSumGM, 0); // % car le pointeur ne valait rien avant, ca valeur va changer
    this->sizeSM = grid.threadByBlock() * sizeof(long);
    }

ReductionLongII::~ReductionLongII()
    {
    GM::free(ptrSumGM);
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void ReductionLongII::run()
    {
    KLongProtocoleII<<<dg,db,sizeSM>>>(ptrSumGM);
    GM::memcpyDToH_long(ptrSum, ptrSumGM);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
