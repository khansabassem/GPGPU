#pragma once

#include "AddVectorUse.h"

/*----------------------------------------------------------------------*\
 |*			Class	 					*|
 \*---------------------------------------------------------------------*/

class AddVector11Use: public AddVectorUse
    {

	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	AddVector11Use(const Grid& grid,bool isVerbose);

	AddVector11Use(bool isVerbose);

	virtual ~ AddVector11Use();

	/*--------------------------------------*\
	|*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/**
	 * override
	 */
	bool filter(const Grid& grid);


    private:

	/**
	 * static
	 */
	static Grid createGrid(int n);

	/*--------------------------------------*\
		|*		Attributs		*|
	 \*-------------------------------------*/

    private:

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
