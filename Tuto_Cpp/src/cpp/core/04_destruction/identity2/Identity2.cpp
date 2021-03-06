#include "Identity2.h"

#include <iostream>

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Identity2::Identity2(int n, double* ptrTab) :
	n(n), ptrTab(ptrTab)
    {
    fill();
    }

Identity2::~Identity2()
    {
    // rien, car aucun new dans le constructeur
    }

/*--------------------------------------*\
 |*		public			*|
 \*-------------------------------------*/

double* Identity2::get()
    {
    return ptrTab;
    }

int Identity2::getN()
    {
    return n;
    }

void Identity2::print()
    {
    for (int s = 1; s <= n * n; s++)
	{
	cout << ptrTab[s - 1] << "\t";

	if (s % n == 0)
	    {
	    cout << endl;
	    }
	}

    cout << endl;
    }

/*--------------------------------------*\
 |*		private			*|
 \*-------------------------------------*/

void Identity2::fill()
    {
    init(0);

    const int JUMP = n + 1;
    for (int s = 0; s < n * n; s += JUMP)
	{
	ptrTab[s] = 1;
	}
    }

void Identity2::init(double value)
    {
    for (int s = 0; s < n * n; s++)
	{
	ptrTab[s] = value;
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

