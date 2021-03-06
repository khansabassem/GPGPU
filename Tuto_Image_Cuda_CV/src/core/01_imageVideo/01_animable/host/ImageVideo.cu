#include <iostream>
#include <assert.h>

#include "ImageVideo.h"
#include "GM.h"

#include "OpencvTools_GPU.h"

using std::cout;
using std::cerr;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern __global__ void toGray(uchar4* ptrDevPixels,uint w, uint h,float t);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

/*-------------------------*\
 |*	Constructeur	    *|
 \*-------------------------*/

ImageVideo::ImageVideo(const Grid& grid , uint w , uint h , string nameVideo) :
	Animable_I<uchar4>(grid, w, h, "ImageVideo_RGBA_uchar4"), //
	nameVideo(nameVideo), //
	capture(nameVideo), //
	matRGBA(h, w, CV_8UC1)
    {
    // Tools
    this->t = 0; // protected dans Animable
    this->sizeImage = sizeof(uchar4) * w * h;

    //video
	{
	bool isOk = capture.start();
	if (!isOk)
	    {
	    cerr << "[ImageVideo] : failed to open : " << nameVideo << endl;
	    exit (EXIT_FAILURE);
	    }
	assert(capture.getW() == w && capture.getH() == h);
	animationStep(); // pour forcer la premiere capture et remplissage ptrTabPixelVideo
	}
    }

ImageVideo::~ImageVideo()
    {
    // rien
    }

/*-------------------------*\
 |*	Methode		    *|
 \*-------------------------*/

/**
 * Override
 * Call periodicly by the API
 *
 * Note : domaineMath pas use car pas zoomable
 */
void ImageVideo::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {
    GM::memcpyHToD(tabPixelsGM, ptrTabPixelVideo, sizeImage);

toGray<<<dg,db>>>(tabPixelsGM,w,h,t);
}

/**
 * Override
 * Call periodicly by the API
 */
void ImageVideo::animationStep()
{
t++;

//video
    {
    Mat matBGR = capture.provideBGR();

    OpencvTools_GPU::switchRB(this->matRGBA, matBGR);
    this->ptrTabPixelVideo = OpencvTools_GPU::castToUchar4(matRGBA);
    }
}

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

