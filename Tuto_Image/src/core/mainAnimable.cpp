#include <iostream>
#include <stdlib.h>

#include "DamierProvider.h"
#include "VagueProvider.h"
#include "VagueGrayProvider.h"
#include "DamierRGBAFloatProvider.h"
#include "DamierHSBAFloatProvider.h"
#include "DamierHueFloatProvider.h"

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

static void vague();
static void damier();
static void vagueGray();
static void damierRGBAFloat4();
static void damierHSBAFloat4();
static void damierHueFloat();

// Tools
template<typename T>
static void animer(Provider_I<T>* ptrProvider , double durationMaxS = 8);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

int mainAnimable()
    {
    cout << "\n[Animable] mode" << endl;

    vague();
    damier();

    vagueGray();
    damierRGBAFloat4();
    damierHSBAFloat4();
    damierHueFloat();

    cout << "\n[Animable] end" << endl;

    return EXIT_SUCCESS;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void vague()
    {
    const double DURATION_MAX_S = 8;

    VagueProvider provider;
    animer<uchar4>(&provider, DURATION_MAX_S);
    }

void damier()
    {
    const double DURATION_MAX_S = 8;

    DamierProvider provider;
    animer<uchar4>(&provider, DURATION_MAX_S);
    }

void vagueGray()
    {
    const double DURATION_MAX_S = 8;

    VagueGrayProvider provider;
    animer<uchar>(&provider, DURATION_MAX_S);
    }

void damierRGBAFloat4()
    {
    const double DURATION_MAX_S = 8;

    DamierRGBAFloatProvider provider;
    animer<float4>(&provider, DURATION_MAX_S);
    }

void damierHSBAFloat4()
    {
    const double DURATION_MAX_S = 8;

    DamierHSBAFloatProvider provider;
    animer<float4>(&provider, DURATION_MAX_S);
    }

void damierHueFloat()
    {
    const double DURATION_MAX_S = 8;

    DamierHueFloatProvider provider;
    animer<float>(&provider, DURATION_MAX_S);
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

