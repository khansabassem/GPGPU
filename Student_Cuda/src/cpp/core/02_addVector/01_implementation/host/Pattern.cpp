#include "Pattern.h"

#include <iostream>
#include <assert.h>
#include <string.h>

using std::string;

/*----------------------------------------------------------------------*\
 |*			Enum	 					*|
 \*---------------------------------------------------------------------*/


string toString(const Pattern& pattern)
    {
    switch(pattern)
	{
	case ENTRELACEMNT: return "ENTRELACEMNT";
	case UN_UN : return "UN-UN";
	}

    assert(false); // ne devrait jamais arriver ici
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
