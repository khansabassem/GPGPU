#pragma once

#include "AddVectorUse.h"

/*----------------------------------------------------------------------*\
 |*			Class	 					*|
 \*---------------------------------------------------------------------*/

class AddVectorBigUse:public AddVectorUse
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	AddVectorBigUse(const Grid& grid,bool isVerbose);

	AddVectorBigUse(bool isVerbose);

	virtual ~ AddVectorBigUse();

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*--------------------------------------*\
		|*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/