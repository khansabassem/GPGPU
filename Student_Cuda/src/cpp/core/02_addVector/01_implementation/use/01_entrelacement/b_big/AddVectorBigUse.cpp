#include "AddVectorBigUse.h"

#include <iostream>

#include "Limits.h"

using std::cout;
using std::endl;
using std::string;
using std::to_string;

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

static const int N=Limits::MAX_INT / 1000;

/*--------------------------------------*\
|*		Constructor		*|
 \*-------------------------------------*/

AddVectorBigUse::AddVectorBigUse(const Grid& grid,bool isVerbose) : //
	AddVectorUse(grid,N, Pattern::ENTRELACEMNT,isVerbose)
    {
    // rien
    }

AddVectorBigUse::AddVectorBigUse(bool isVerbose)://
	AddVectorBigUse(createGrid(),isVerbose)
    {
// rien
    }

AddVectorBigUse::~AddVectorBigUse()
    {
    //rien
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
