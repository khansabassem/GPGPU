#include <iostream>
#include <math.h>

#include "VectorTools.h"
#include "HM.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		MM			*|
 \*-------------------------------------*/

static bool IS_MEMORY_DMA = true; // TODO AddVector try both, increase bandwidth H -> D and D -> H

bool VectorTools::isDMA()
    {
    return IS_MEMORY_DMA;
    }

float* VectorTools::create(int n)
    {
    if (!IS_MEMORY_DMA)
	{
	return new float[n];
	}
    else
	{
	float* ptr;
	HM::malloc(&ptr, n * sizeof(float));
	return ptr;
	}
    }

void VectorTools::free(float* ptrV)
    {
    if (!IS_MEMORY_DMA)
	{
	delete[] ptrV;
	}
    else
	{
	HM::free(ptrV);
	}
    }

/*--------------------------------------*\
 |*	Methode	public (static)		*|
 \*-------------------------------------*/

bool VectorTools::isAddVector_Ok(float* ptrV1 , float* ptrV2 , float* ptrW , int n)
    {
    float* ptrResult = create(n);

    addVectorCPU(ptrV1, ptrV2, ptrResult, n);
    bool isOk = isEquals(ptrResult, ptrW, n, 1e-6); // comparer version cpu (ptrResult) avec version gpu (ptrW)

    free(ptrResult);

    return isOk;
    }

/**
 * 1 2 3 4 5
 */
float* VectorTools::createV1(int n)
    {
    float* ptrV = create(n);

    for (int i = 0; i < n; i++)
	{
	ptrV[i] = i + 1;
	}

    return ptrV;
    }

/**
 * 10 20 30 40 50
 */
float* VectorTools::createV2(int n)
    {
    float* ptrV = create(n);

    for (int i = 0; i < n; i++)
	{
	ptrV[i] = (i + 1) * 10;
	}

    return ptrV;
    }

void VectorTools::print(float* ptrV , int n)
    {
    cout << endl;
    for (int i = 0; i < n; i++)
	{
	cout << ptrV[i] << "\t";
	}
    cout << endl;
    }

/*--------------------------------------*\
 |*	Methode	private (static)	*|
 \*-------------------------------------*/

/**
 * v1,v2,w same size
 */
void VectorTools::addVectorCPU(float* ptrV1 , float* ptrV2 , float* ptrW , int n)
    {
    for (int i = 0; i < n; i++)
	{
	ptrW[i] = ptrV1[i] + ptrV2[i];
	}
    }

/**
 * simple
 */
bool VectorTools::isEquals(float* ptrV1 , float* ptrV2 , int n , float epsilon)
    {
    for (int i = 1; i <= n; i++)
	{
	float delta = fabs(*ptrV1 - *ptrV2);

	if (delta > epsilon)
	    {
	    return false;
	    }

	ptrV1++;
	ptrV2++;
	}

    return true;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

