#include "AddVector.h"

#include <iostream>
#include <assert.h>

#include "Kernel.h"
#include "GM.h"
#include "Bandwidth.h"
#include "VectorTools.h"

using std::cout;
using std::endl;
using std::to_string;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addVector(float* ptrDevV1, float* ptrDevV2, float* ptrDevW,int n);
extern __global__ void addVector11(float* ptrDevV1, float* ptrDevV2, float* ptrDevW, int n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

AddVector::AddVector(const Grid& grid , float* ptrV1 , float* ptrV2 , float* ptrW , int n , Pattern pattern,bool isVerbose) :
	RunnableGPU(grid, title() + "-" + toString(pattern) + "-" + to_string(n),isVerbose), // classe parente
//
	ptrV1(ptrV1), //
	ptrV2(ptrV2), //
	ptrW(ptrW), //
	n(n), //
	pattern(pattern)

    {
    this->sizeVector = sizeof(float)*n; // TODO AddVector // octet

    // MM (malloc Device)
	{
	GM::malloc(&ptrDevV1, sizeVector); //gm pour global memory
	GM::malloc(&ptrDevV2, sizeVector);
	GM::malloc(&ptrDevW, sizeVector);

	}

    }

AddVector::~AddVector(void)
    {
    //MM (device free)
	{
	GM::free(ptrDevV1);
	GM::free(ptrDevV2);
	GM::free(ptrDevW);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * override
 */
void AddVector::run()
    {
    // MM (copy Host->Device)
	{
	Bandwidth bandwidth(sizeVector * 2, "[" + title() + "] : Host -> GM :");

	GM::memcpyHToD(ptrDevV1, ptrV1, sizeVector);
	GM::memcpyHToD(ptrDevV2, ptrV2, sizeVector);
	// TODO AddVector

	if (isVerbose) // dans Runable ou RunnableGPU
	    {
	    cout << bandwidth << endl;
	    }
	}

    switch (pattern)
	{
    case ENTRELACEMNT:
	{
	addVector<<<dg,db>>>(ptrDevV1, ptrDevV2, ptrDevW, n);
	break;
	}

    case UN_UN:
	{
	assert(db.x * db.y * db.z * dg.x * dg.y * dg.z == n);
	addVector11<<<dg,db>>>(ptrDevV1, ptrDevV2, ptrDevW, n);
	break;
	}

    default:
	{
	assert(false);
	break;
	}
	}

// MM (Device -> Host)
	{
	Bandwidth bandwidth(sizeVector, "[" + title() + "] : GM -> Host :");
	//barriere de memo implicite
	GM::memcpyDToH(ptrW, ptrDevW, sizeVector); // ce qui est à droite va à gauche
	// on ne sait pas si le kernel a terminé le travail.

	if (isVerbose)
	    {
	    cout << bandwidth << endl; // best with DMA in VectorTools
	    }
	}
    }

/**
 * override
 */
double AddVector::getInputGO()
    {
    return ((long)2 * (long)n * (long)sizeof(float)) / (double)((long)1024 * (long)1024 * (long)1024);
    }

/**
 * override
 */
double AddVector::getOutputGO()
    {
    return ((long)1 * (long)n * (long)sizeof(float)) / (double)((long)1024 * (long)1024 * (long)1024);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

string AddVector::title()
    {
    if (VectorTools::isDMA())
	{
	return "Addvector-DMA";
	}
    else
	{
	return "Addvector";
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
