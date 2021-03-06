#include "Carrer.h"


#include <iostream>
using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Carrer::Carrer(string name, double coter) :
	Rectangle(name, coter, coter)
    {
    // rien de plus
    }

/**
 * destructeur classe parente appeler automatiquement
 */
Carrer::~Carrer()
    {
    // rien, car aucun new dans constructeur

    // debug pedagogique
       	{
       	cout << "[Carrer] : destructeur : " << getName()<<" : ";
       	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

