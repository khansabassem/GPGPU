#include "SliceSM.h"

#include <iostream>
#include <assert.h>

#include "GM.h"
#include "SM.h"

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void sliceSM(int nbSlice,float* ptrPiHatGM);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

SliceSM::SliceSM(const Grid& grid , int nbSlice , double* ptrPiHat , bool isVerbose) :
	RunnableGPU(grid, "SliceSM-" + to_string(nbSlice), isVerbose), // classe parente
	//
	ptrPiHat(ptrPiHat), //
	nbSlice(nbSlice) //
    {
    this->ptrPiHatGM = NULL;
    this->sizeSM = grid.threadByBlock() * sizeof(float);

    // MM
	{
	GM::malloc0(&ptrPiHatGM, sizeof(float));
	}
    }

SliceSM::~SliceSM(void)
    {
    //MM
	{
	GM::free(ptrPiHatGM);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void SliceSM::run()
    {
    // Etape 1 : lancer le kernel
    // Etape 2 : recuperer le resultat coter host (par exemple avec memcpyDToH_float)
    // Etape 3 : finaliser le calcul de PI

    // TODO SliceSM
    //1
    sliceSM<<<dg,db,sizeSM>>>(nbSlice , ptrPiHatGM);
    //2
    float result = 0.0;
    GM::memcpyDToH_float(&result, ptrPiHatGM);
    //3
    *ptrPiHat = (double)result;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
