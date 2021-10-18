#include <iostream>

#include "ImageVideoProvider.h"

#include "Args.h"
#include "Viewer_CPU.h"
using namespace cpu;

using std::cout;
using std::endl;

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/


int mainImage(const Args& args)
    {
    cout << "\n[Image] mode" << endl;

    GLUTImageViewers::init(args.argc, args.argv); // only once

    // ImageOption : (boolean,boolean) : (isSelection,isAnimation=true)
    ImageOption zoomable(true);
    ImageOption nozoomable(false);

    Viewer<ImageVideoProvider> imageVideo(nozoomable, 0, 0); 				//  imageOption px py

    GLUTImageViewers::runALL();  // Bloquant, Tant qu'une fenetre est ouverte

    cout << "\n[Image] end" << endl;

    return EXIT_SUCCESS;
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

