#include "Prix.h"


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Prix::Prix(int prix, string objet) :
	prix(prix), objet(objet)

    {
    // rien de plus
    }

Prix::~Prix()
    {
    // rien, car pas de new dans constructeur
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

int Prix::getPrix()
    {
    return prix;
    }

string Prix::getObjet()
    {
    return this->objet;
    }

/**
 * surcharge
 *
 * fiend
 */
Prix operator+(const Prix& prix1, const Prix& prix2)
    {
    int prixTotal=prix1.prix + prix2.prix;
    string objet=prix1.objet + " " + prix2.objet;

    Prix prix(prixTotal, objet);

    return prix;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

