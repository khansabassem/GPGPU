#pragma once

#include "Use_I.h"
#include "Grid.h"
#include "RunnableGPU_I.h"

#include "UseReductionLong.h"

/*----------------------------------------------------------------------*\
 |*			Class	 					*|
 \*---------------------------------------------------------------------*/

class UseReductionLongII: public UseReductionLong
    {
	/*------------------------------------------------------------*\
        |*			Constructors 			      *|
	 \*------------------------------------------------------------*/

    public:

	/**
	 * db power 2
	 */
	UseReductionLongII(const Grid& grid,bool isVerbose);

	UseReductionLongII(bool isVerbose);

	virtual ~UseReductionLongII();

	/*------------------------------------------------------------*\
        |*			Methodes 			      *|
	 \*------------------------------------------------------------*/



	/*------------------------------------------------------------*\
        |*			Attributs			      *|
	 \*------------------------------------------------------------*/



    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
