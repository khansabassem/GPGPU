#include <iostream>

#include "RipplingProvider.h"
#include "MandelbrotProvider.h"

#include "RaytracingProviderGM.h"
#include "RaytracingProviderCM.h"
#include "RaytracingProviderCM2SM.h"
#include "RaytracingProviderSM.h"
#include "NewtonProvider.h"


#include "SceneCubeCreator.h"

//#include "VagueProvider.h"
//#include "DamierProvider.h"
//
//#include "VagueGrayProvider.h"
//#include "DamierRGBAFloatProvider.h"
//#include "DamierHSBAFloatProvider.h"
//#include "DamierHueFloatProvider.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

SceneCubeCreator::SceneCubeCreator()
    {
    createImages();
    createScene();
    }

SceneCubeCreator::~SceneCubeCreator()
    {
    delete ptrImage1;
    delete ptrImage2;
    delete ptrImage3;
    delete ptrImage4;
    delete ptrImage5;
    delete ptrImage6;

    delete ptrScene;
    }

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

SceneCube* SceneCubeCreator::getScene()
    {
    return ptrScene;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void SceneCubeCreator::createImages()
    {
    ptrImage2 = NewtonProvider().createImageGL();
    ptrImage1 = MandelbrotProvider().createImageGL();
    ptrImage3 = RipplingProvider().createImageGL();
    ptrImage4 = RaytracingProviderGM().createImageGL();
    ptrImage5 = RaytracingProviderSM().createImageGL();
    ptrImage6 = RaytracingProviderCM2SM().createImageGL();


//    ptrImage1 = VagueProvider().createImageGL();
//    ptrImage2 = DamierProvider().createImageGL();
//
//    ptrImage3 = VagueGrayProvider().createImageGL();
//    ptrImage4 = DamierRGBAFloatProvider().createImageGL();
//    ptrImage5 = DamierHSBAFloatProvider().createImageGL(); //ko, FIXME JST shader
//    ptrImage6 = DamierHueFloatProvider().createImageGL(); // ko, FIXME JST shader
    }

void SceneCubeCreator::createScene()
    {
    ptrScene = new SceneCube(ptrImage1, ptrImage2, ptrImage3, ptrImage4, ptrImage5, ptrImage6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

