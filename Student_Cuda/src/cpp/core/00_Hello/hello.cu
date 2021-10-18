// Attention : Extension .cu

#include <iostream>
#include <stdio.h>
#include "cudas.h"
#include "GM.h"
#include "Kernel.h"

using std::cout;
using std::endl;

/**
 * http://www.icl.utes3/docs/cuda.htmk.edu/~mgatl
 */

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

__global__ static void addScalar(int a , int b , int* ptrDevSum);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Host			*|
 \*-------------------------------------*/

__host__ void addScalar() // __host__ facultatif
    {
    int a = 10;
    int b = 1;
    int sum;

    int* ptrSum = &sum;	// on host (CPU)
    int* ptrDevSum; 	// on device (GPU)

    // MM (memory managment)
    size_t size = sizeof(int); // [octet]
    GM::malloc(&ptrDevSum, size); // Device memory allocation (*)

    // Grid : Specifier number thread : ici 1 thread au total !
    dim3 dg(1, 1, 1);
    dim3 db = dim3(1, 1, 1); // syntaxe alternative

    addScalar<<<dg,db>>>(a,b,ptrDevSum); // asynchrone, call le kernel GPU addScalar

    Kernel::synchronize(); // necessaire only pour printf sur device

    // MM (memory management)
	{
	GM::memcpyDToH(ptrSum, ptrDevSum, size);   // Device -> Host, MM = barrier de synchronisation
	GM::free(ptrDevSum); //  free memory create in (*)
	}

    cout << "\n[Hello : Host   side : addScalar] " << a << " + " << b << " = " << sum << endl;
    }

/*--------------------------------------*\
 |*		Device			*|
 \*-------------------------------------*/

/**
 * Hyp : 1 seul thread, ie dg(1,1,1) et db (1,1,1)
 */
__global__ void addScalar(int a , int b , int* ptrDevSum)
    {
    *ptrDevSum = a + b; // Hyp: 1 seul thread (pas besoin de plus, pour additioner 2 nombre)

    // debug
    printf("[Hello : Device side : addScalar] %d + %d = %d", a, b, *ptrDevSum); // requiert  Kernel::synchronize() in host side after kernel
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

