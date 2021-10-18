#include "AddVector11Use.h"

#include <iostream>
#include <assert.h>

using std::cout;
using std::endl;
using std::string;
using std::to_string;

/*--------------------------------------*\
 |*		Imported		*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

static const int N=9;

/*--------------------------------------*\
|*		Constructor		*|
 \*-------------------------------------*/

AddVector11Use::AddVector11Use(const Grid& grid,bool isVerbose) : //
	AddVectorUse(grid, N, Pattern::UN_UN,isVerbose)
    {
    assert(filter(grid));
    }

AddVector11Use::AddVector11Use(bool isVerbose)//
	:AddVector11Use(createGrid(N),isVerbose)
    {
    //rien
    }

AddVector11Use::~AddVector11Use()
    {
    //rien
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

/**
 * override
 */
bool AddVector11Use::filter(const Grid& grid)
    {
    return Use_I::filter(grid) && grid.threadCounts() == getN();
    }

/*--------------------------------------*\
|*		Private			*|
 \*-------------------------------------*/

/**
 * static
 */
Grid AddVector11Use::createGrid(int n)
    {
    const bool IS_CHECK_HEURISTIC=false; // grid(dg,db,IS_CHECK_HEURISTIC);

    // Contraintes :
    //	(C1) nombre de thread == n
    //	(C2) max(dg.x*dg.y*dg.z)<=1024
    dim3 dg(1,1,1);
    dim3 db(1,n,1); //9 car 9 thread pattern 1,1 pas sympa du tout, et taille
    // de la grille est subit. ==> pattern catastrophique.
    Grid grid( dg, db, 1);

    // Questions:
    //	(Q1) Facile a faire cette grid dans le cas general? pour utiliser a la fois dg et db?
    //	(Q2) Toujours possible d'utilisere dg et db?

    assert(grid.threadCounts() == n);

    return grid;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
