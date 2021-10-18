#include "Thread2D.h"
#include "cudas.h"

#include "real.h"
#include "MandelbrotMath.h"

#include "DomaineMath_GPU.h"
#include "Indices_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

__global__ void mandelbrot(uchar4* tabPixelsGM , uint w , uint h , DomaineMath domaineMath , int n)
    {
    MandelbrotMath mandelbrotMath(n);
    const int TID = Thread2D::tid();
    const int NB_THREAD = Thread2D::nbThread();
    const int WH = w * h;
    int pixelI, pixelJ;
    double x = 0, y = 0;
    int s = TID;
    while(s<WH){
	Indices::toIJ(s, w, &pixelI, &pixelJ);
	domaineMath.toXY(pixelI, pixelJ, &x, &y);

	mandelbrotMath.colorXY(&tabPixelsGM[s], (real)x, (real)y);
	s+= NB_THREAD;
        }
    // appeler colorXY

    // Probleme : Choix a faire pour le type de (x,y) :
    //
    //			- Travailler en float pour plus de performance?
    //			- Travailler en double pour pouvoir zoomer plus loin dans le fractale?
    //
    // Solution : Travailler avec le typedef real definit dans "real.h"
    //		  Specifier dans "real.h" si vous souhaitez travailler en float ou en double
    //	          Ainsi on passe facilement et proprement d'une version float a une version double
    //
    // Note : domaineMath.toXY travaille lui toujours en double pour vous permettre les deux possibilites ci-dessus
    //
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

