#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "Homme.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useSurchargeCout(void);

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void use0(void);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

void useSurchargeCout(void)
    {
    cout << "\nHomme : useSurchargeCout" << endl;

    use0();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void use0(void)
    {
    Homme homme(180, 55);
    cout << homme << endl;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

