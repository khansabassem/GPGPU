#include "ImageVideoProvider.h"
#include "ImageVideo.h"
#include "VideoProvider.h"

#include <iostream>

#include "ImageAnimable_CPU.h"
using namespace cpu;

using std::string;

/*--------------------------------------*\
 |*		Surcharge		*|
 \*-------------------------------------*/

/**
 * Override
 */
Animable_I<uchar4>* ImageVideoProvider::createAnimable(void)
    {
    int w;
    int h;
    string fileVideo = VideoProvider::neilpryde(&w, &h);

    return new ImageVideo(w, h, fileVideo);
    }

/**
 * Override
 */
Image_I* ImageVideoProvider::createImageGL(void)
    {
    ColorRGB_01 colorTexte(1, 0, 0); // red
    return new ImageAnimable_RGBA_uchar4(createAnimable(), colorTexte);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
