#include "AddVectorSmallUse.h"

#include <iostream>

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

static const int N=9;

/*--------------------------------------*\
|*		Constructor		*|
 \*-------------------------------------*/

AddVectorSmallUse::AddVectorSmallUse(const Grid& grid,bool isVerbose) : //
	AddVectorUse(grid,N, Pattern::ENTRELACEMNT,isVerbose)
    {
    // rien
    }

AddVectorSmallUse::AddVectorSmallUse(bool isVerbose) : //
	AddVectorSmallUse(createGrid(),isVerbose)
    {
// rien
    }

AddVectorSmallUse::~AddVectorSmallUse()
    {
    //rien
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
