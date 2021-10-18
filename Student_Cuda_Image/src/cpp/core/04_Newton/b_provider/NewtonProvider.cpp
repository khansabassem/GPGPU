#include "NewtonProvider.h"
#include "Newton.h"
#include "cuda_runtime.h"
#include "Maths.h"
#include "Grid.h"
#include "Hardware.h"
#include "UseFromProvider.h"

#include <assert.h>

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* NewtonProvider::createAnimable(bool isVerbose)

    {
//    DomaineMath domaineMath = DomaineMath(-2,-2,2,2);

//    int dw = 600 ; // =32*30=960
//    int dh = 600; // =32*30=960

    float dt = 2 * PI / 8000;

    // grid cuda
    int mp = Hardware::getMPCount();//68
    int coreMP = Hardware::getCoreCountMP();//64
//
    dim3 dg(mp, 1, 1);  	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
    dim3 db(1024, 1, 1);   	// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//    dim3 db(Grid::dbMax.x, 1, 1);
//    dim3 dg(mp, 1, 1);  		// disons, a optimiser selon le gpu, peut drastiqument ameliorer ou baisser les performances
//    dim3 db(2, 1, 1);
    Grid grid(dg, db);
//    return new Newton(grid, dw, dh, nMin, nMax, domaineMath);
    return createAnimable(grid, isVerbose);
    }

Animable_I<uchar4>* NewtonProvider::createAnimable(const Grid& grid , bool isVerbose)
    {
    // Animation;
    int nMin = 100;// 100
    int nMax = 1000; // 100

    // Domaine init
    double x1 = -4;
    double y1 = -4;
    double x2 = 4;
    double y2 = 4;
    DomaineMath domaineMath(x1, y1, x2, y2);

    // Dimension
    int w = 16 * 80;
    int h = 16 * 60;

    return new Newton(grid, w, h, nMin, nMax, domaineMath);
    }

Image_I* NewtonProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 1, 0); // black
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }
/**
 * override
 */
Use_I* NewtonProvider::createUse(const Grid& grid , bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, grid, isVerbose);
    }

/**
 * override
 */
Use_I* NewtonProvider::createUse(bool isVerbose)
    {
    return new UseFromProvider<uchar4>(this, isVerbose);
    }
/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
