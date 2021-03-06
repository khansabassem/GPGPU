#include "DomaineProvider.h"
#include "DamierProvider.h"
#include "ImageCustomDomaine.h"

#include "DomaineMath_CPU.h"
using namespace cpu;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

Animable_I<uchar4>* DomaineProvider::createAnimable()
    {
    DamierProvider damierProvider;

    return damierProvider.createAnimable();
    }

Image_I* DomaineProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(0, 0, 0); // black
    return new ImageCustomDomaine(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
