#include "AddScalar.h"

#include <iostream>
#include <assert.h>
#include "GM.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void addScalar(float a, float b, float* ptrDevSum);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur			*|
 \*-------------------------------------*/

AddScalar::AddScalar(float a , float b , float* ptrSum) :
	a(a),//
	b(b), //
	ptrSum(ptrSum)
    {
    this->sizeFloat = sizeof(float); // [octet]

    // MM
	{
	GM::malloc(&prtDevSum, sizeFloat);
	}
    }

AddScalar::~AddScalar(void)
    {
    //MM
	{
	GM::free(prtDevSum);
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

void AddScalar::run()
    {
    // Grid : specifier le nombre de thread
    dim3 dg(1, 1, 1);
    dim3 db(1, 1, 1);
    assert(dg.x * dg.y * dg.z * db.x * db.y * db.z == 1);// 1 seul thread suffit

    addScalar<<<dg,db>>>(a, b, prtDevSum); // assynchrone

    //Device::synchronize(); // necessaire only pour printf coter device

    // MM (Device -> Host)
	{
	GM::memcpyDToH(ptrSum, prtDevSum, sizeFloat); // MM = barriere synchronisation implicite
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
