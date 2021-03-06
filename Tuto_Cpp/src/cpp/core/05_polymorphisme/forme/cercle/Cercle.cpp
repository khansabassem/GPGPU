#include "Cercle.h"

#include <math.h>


#include <iostream>
using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Cercle::Cercle(string name, double rayon) :
	Forme_A(name), rayon(rayon)
    {
    // rien de plus
    }

/**
 * destructeur classe parente appeler automatiquement
 */
Cercle::~Cercle()
    {
    // rien, car aucun new dans constructeur

    // debug pedagogique
       	{
       	cout << "[Cercle] : destructeur : " << getName()<<" : ";
       	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
double Cercle::aire(void)
    {
    return M_PI*rayon*rayon;
    }

/**
 * Override
 */
double Cercle::perimetre()
    {
    return 2*rayon*M_PI;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

