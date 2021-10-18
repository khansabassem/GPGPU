#pragma once
#include "cuda_runtime.h"
#include "cudas.h"
#include "Maths.h"
#include "Variateur_GPU.h"
#include "Animable_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class Newton: public Animable_I<uchar4>
    {
	/*--------------------------------------*\
	|*		Constructor		*|
	 \*-------------------------------------*/

    public:

	Newton(const Grid& grid , uint w , uint h , uint nMin, uint nMax , const DomaineMath& domaineMath);
	virtual ~Newton(void);
	/*--------------------------------------*\
	 |*		Methodes		*|
	 \*-------------------------------------*/

    public:

	/*-------------------------*\
	|*   Override Animable_I   *|
	 \*------------------------*/

	/**
	 * Call periodicly by the api
	 */
	virtual void process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath);

	/**
	 * Call periodicly by the api
	 */
	virtual void animationStep();

	//by me
	virtual float getAnimationPara();
	virtual int getW();
	virtual int getH();
	virtual string getTitle(void);
//	virtual DomaineMath* getDomaineMathInit(void);


	/*--------------------------------------*\
	 |*		Attributs		*|
	 \*-------------------------------------*/

    private:

	// Inputs
	uint w;
	uint h;
	uint n;

	// Tools
	Variateur<int> variateurN;

	dim3 dg;
	dim3 db;
	DomaineMath* ptrDomaineMathInit;

	//output

	string title;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
