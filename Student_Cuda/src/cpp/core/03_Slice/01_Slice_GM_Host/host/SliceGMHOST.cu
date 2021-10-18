#include "SliceGMHOST.h"

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
// import du kernel
extern __global__ void reductionIntraThreadGMHOST(float* tabGM,int nbSlice);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

SliceGMHOST::SliceGMHOST(Grid grid , int nbSlice , double* ptrPiHat , bool isVerbose) :
	RunnableGPU(grid, "SliceGM-HOST-" + to_string(nbSlice), isVerbose), // classe parente
//
	nbSlice(nbSlice), //
	ptrPiHat(ptrPiHat) //
    {
    // ntabGM
	{
	this->nTabGM = grid.threadCounts();

	// Warning : Advanced : Et si plus de threads que slices? complique! (pas utile de le coder)
	}

    // MM
	{
	this->sizeTabGM = nTabGM * sizeof(float); // [octet]
	// step 0
	GM::malloc(&tabGM, sizeTabGM);
	}

    }

SliceGMHOST::~SliceGMHOST(void)
    {
    //step 4
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
 *	Etape 0 : Promotion d'un tableau en GM (MemoryManagement MM)		(Dans le constructeur)
 * 	Etape 1 : Reduction intra-thread dans un tableau promu en GM
 * 	Etape 2 : Copy du tableau coter host
 * 	Etape 3 : Reduction parallel du tableau coter host avec OMP
 * 	Etape 4 : Destruction GM						(Dans le destructeur)
 *
 * </pre>
 */
void SliceGMHOST::run()
    {
    // step 1
    //reductionIntraThreadGMHOST<<<dg,db>>>(tabGM, nbSlice);
    reductionIntraThreadGMHOST<<<grid.dg,grid.db>>>(tabGM, nbSlice);
    // step 2 et 3
    reductionHost();
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/**
 * Reduction paralle sur cpu du tableau promu en GM, ramener coter host
 */
void SliceGMHOST::reductionHost()
    {
    // 1) Creer un tableau sur la pile de bonne dimension
    // 2) Transferer la tabGM dedans
    // 3) reduction parallel avec OMP
    // 4) finalisation du calcul de ptrPiHat

    // 1
    float tab[nTabGM]; // chaque thread a une case pour mettre son résultat
    float const dx = 1 / (float)nbSlice;
    // 2
    GM::memcpyDToH(tab, tabGM, sizeTabGM);
    // 3
    float sum = 0;
#pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < this->nTabGM; i++)
	{
	sum += tab[i];
	}
    // 4
    *ptrPiHat = sum * dx;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
