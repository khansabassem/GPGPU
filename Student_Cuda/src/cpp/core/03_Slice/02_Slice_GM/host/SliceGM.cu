#include "SliceGM.h"

#include <iostream>
#include <assert.h>

#include "GM.h"
#include "Maths.h"
#include "Hardware.h"
#include "Kernel.h"

using std::cout;
using std::endl;
using std::to_string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void reductionIntraThreadGM(float* tabGM,int nbSlice);
extern __global__ void ecrasementGM(float* tabGM, int moitier);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

SliceGM::SliceGM(Grid grid , int nbSlice , double* ptrPiHat , bool isVerbose) :
	RunnableGPU(grid, "SliceGM-" + to_string(nbSlice), isVerbose), // classe parente
//
	nbSlice(nbSlice), //
	ptrPiHat(ptrPiHat) //
    {
    // ntabGM
	{
	this->nTabGM = grid.threadCounts();

	}

    // MM
	{
	this->sizeTabGM = nTabGM * sizeof(float); // [octet]
	// step 0
	GM::malloc(&tabGM, sizeTabGM);

	}
    }

SliceGM::~SliceGM(void)
    {
    //MM (device free)
	{
	GM::free(tabGM);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * <pre>
 * Idea globale
 *
 *	Etape 0 : Promotion d'un tableau en GM (MemoryManagement MM)
 * 	Etape 1 : Reduction intra-thread dans un tableau promu en GM
 * 	Etape 2 : Reduction du tableau en GM par ecrasement hierarchique 2 à 2
 * 		  On lance les kernels d'ecrasement depuis le host (chef d'orchestre)
 * 	Etape 4 : Copy du reseultat coter host
 * 	Etape 5 : Destruction GM
 * </pre>
 */
void SliceGM::run()
    {
    // step 1
    reductionIntraThreadGM<<<grid.dg,grid.db>>>(tabGM, nbSlice);
    // step 2 et 4
    reductionGM();

    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Etape 1 : Lancement des kernels d'ecrasement depuis le host, dans une boucle,
 * Etape 2 : recuperer le resultat coter host
 * Etape 3 : finaliser le calcule de PI
 */
void SliceGM::reductionGM()
    {
    int middle = nTabGM >> 1; // nTabGM/2;
    float const dx = 1 / (float)nbSlice;
    //printf("middle: %d\n",middle);
    // Si la premiere grid n'est pas une puissance de 2... comment faire mtn ?
    dim3 dg = dim3(grid.dg.x, 1, 1);
    dim3 db = dim3(grid.db.x, 1, 1);
    while (middle > 0)
	{
	if (dg.x > 1)
	    dg.x = dg.x >> 1;
	else
	    db.x = db.x >> 1;
	ecrasementGM<<<dg,db>>>(tabGM, middle);
	middle = middle >> 1;

	}
    // 3 pas nécessaire de récuper tout le tableau, uniquement la dernière case.
    float result(0); //pourquoi est-il impossible de déclarer un pointeur ici ?

    GM::memcpyDToH_float(&result, tabGM); // on prend la première valeur donc ok

    // 4
    *ptrPiHat = result * dx;

    // Utiliser une autre grille que celle heriter de la classe parente dg, db
    // Votre grid ici doit avoir une taille speciale!
    // N'utiliser donc pas les vraibales dg et db de la super classe
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
