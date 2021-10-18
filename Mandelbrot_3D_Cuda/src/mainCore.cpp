#include <iostream>

#include "GLUTWindowScene.h"
#include "GLUTWindowManagers.h"
#include "Args.h"
#include "SurfaceSceneStrip.h"

#include "Mandelbrot3DProvider.h"

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

void mainCore(const Args& args)
    {
    GLUTWindowManagers::init(args.argc, args.argv);

    SurfaceStrip_I* ptrSurfaceStrip = Mandelbrot3DProvider::createSurfaceStrip();

    SurfaceSceneStrip* ptrScene = new SurfaceSceneStrip(ptrSurfaceStrip);
    ptrScene->setAppearance(RenderMode::RENDER_MODE_FILL);

    GLUTWindowScene window(ptrScene, "3D Surface Mandlebrot", 1024, 768, 10, 10);

    GLUTWindowManagers::getInstance()->runALL(); // bloquant

    delete ptrScene;
    delete ptrSurfaceStrip;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
