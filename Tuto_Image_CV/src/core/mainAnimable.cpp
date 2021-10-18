#include <iostream>
#include <stdlib.h>

#include "ImageVideoProvider.h"

#include "AnimatorImage_CPU.h"
using namespace cpu;

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

static void imageVideo();

// Tools
template<typename T>
static void animer(Provider_I<T>* ptrProvider , double durationMaxS = 8);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainAnimable()
    {
    cout << "\n[Animable] mode" << endl;

    imageVideo();

    cout << "\n[Animable] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void imageVideo()
    {
    const double DURATION_MAX_S = 8;

    ImageVideoProvider provider;
    animer<uchar4>(&provider, DURATION_MAX_S);
    }

/*-----------------------------------*\
 |*		Tools	        	*|
 \*-----------------------------------*/

template<typename T>
void animer(Provider_I<T>* ptrProvider , double durationMaxS)
    {
    const bool isVerbosityEnable = true;

    Animable_I<T>* ptrAnimable = ptrProvider->createAnimable();

    AnimatorImage<T> animator(ptrAnimable, isVerbosityEnable, durationMaxS);
    animator.run();

    delete ptrAnimable;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

