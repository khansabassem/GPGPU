#include <iostream>
#include <assert.h>

#include "AddScalar.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool isAddScalar_Ok()
    {
    float a = 8;
    float b = 80;
    float sum;

    // Partie interessante GPGPU
	{
	AddScalar addScalar(a, b, &sum);
	addScalar.run();
	}

    cout << "[addScalar objet] " << a << " + " << b << " = " << sum << endl;
    assert(sum == a + b);
    bool isOk = (sum == a + b);

    return isOk;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

