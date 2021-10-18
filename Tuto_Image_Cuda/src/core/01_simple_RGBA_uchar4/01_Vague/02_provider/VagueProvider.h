#pragma once

#include "cudas.h"

#include "ProviderUse_I.h"

#include "Provider_I_GPU.h"
using namespace gpu;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/**
 * Observation:
 * 	Les objets retournees sont sur le tas (2 ptr)
 *
 * Destruction:
 * 	4 cas d'utilisation:
 * 		- Image
 * 		- Animable
 * 		- ForceBrut
 * 		- Barivox
 *
 * 	Cas Image:
 * 		Le viewer s'occupe d'effacer:
 * 			- Image_I*
 * 			- Animable_I<uchar4>*
 * 	Cas Animable:
 *		L'animator detruit animable
 *
 * 	Cas ForceBrut:
 * 		Force brut utilise animator qui detruit animable
 *
 * 	Cas Barivox:
 * 		Barivox detruit
 *
 * 	Autre cas:
 * 		A vous de detruire les objets
 *
 */
class VagueProvider: public Provider_I<uchar4>, ProviderUse_I
    {
    public:

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(bool isVerbose = true);

	/**
	 * Override
	 */
	virtual Animable_I<uchar4>* createAnimable(const Grid& grid , bool isVerbose = false);

	/**
	 * Override
	 */
	virtual Image_I* createImageGL();

	/**
	 * Override
	 */
	virtual Use_I* createUse(const Grid& grid , bool isVerbose = false);

	/**
	 * Override
	 */
	virtual Use_I* createUse(bool isVerbose = true);

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

