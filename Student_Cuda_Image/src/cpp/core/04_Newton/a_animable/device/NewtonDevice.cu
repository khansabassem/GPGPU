#include "Thread2D.h"
#include "Thread1D.h"
#include "cudas.h"

#include "NewtonMath.h"

#include "Indices_GPU.h"
#include "DomaineMath_GPU.h"

//by me
#include "Hardware.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

__global__ void newton(uchar4* tabPixelsGM, uint w, uint h, DomaineMath domaineMath, uint n);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

//by me
__global__ void newton(uchar4* ptrDevPixels, uint w, uint h, DomaineMath domaineMath, uint n)
    {
    float epsilon =0.1f*powf(0.90f,n);// 0.1f;
    NewtonMath newtonMath = NewtonMath(epsilon, n);

    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();

    const int WH = w * h;

    uchar4 color;

    double x;
    double y;

    int pixelI;
    int pixelJ;

    int s = TID;
    while (s < WH)
	{
	Indices::toIJ(s, w, &pixelI, &pixelJ); // update (pixelI, pixelJ)

	// (i,j) domaine ecran
	// (x,y) domaine math
	domaineMath.toXY(pixelI, pixelJ, &x, &y); //  (i,j) -> (x,y)

	newtonMath.colorXY(&color, x, y); // update color

	ptrDevPixels[s] = color;

	s += NB_THREAD;
	}
//__global__ void newton(uchar4* tabPixelsGM, uint w, uint h, DomaineMath domaineMath, uint n)
//    {
//    //by me
//    float epsilon = 0.1f*powf(0.90f,n);//n varies with time so does epsilon
//    NewtonMath newtonMath = NewtonMath(epsilon, n/2);
//// until here by me
//    const int TID = Thread2D::tid();//();
//    const int NB_THREAD = Thread2D::nbThread();
//    const int WH = w * h;
//    const int LEAP = blockDim.x * gridDim.x;
//// by    me4
//    uchar4 color;
//// until here
//    double x;
//    double y;
//
//    // added 2020.8.26
//    int idx = blockIdx.x * blockDim.x + threadIdx.x;
//    int i; // in [0,h[
//    int j; // in [0,w[
//
//    int s = TID;
//    while (s < WH)
////    while (idx < WH)
//	{
//	Indices::toIJ(s, w, &i, &j); // update (i, j)// ok
////
//	i=blockIdx.x;
//	j=threadIdx.x;
//
//	i = idx / w;
//	j = idx % w;
//	// (i,j) domaine ecran
//	// (x,y) domaine math
//	domaineMath.toXY(i, j, &x, &y); //  (i,j) -> (x,y) ok
//	newtonMath.colorXY(&color, x, y); // update color
//	tabPixelsGM[idx] = color;

//	 s += NB_THREAD;
////	idx += LEAP;
//	}


    }

/*-----------------------------------a-----------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

