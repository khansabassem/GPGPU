#include "Raytracing.h"

#include <iostream>

#include "MM.h"
#include "GM.h"
#include <assert.h>
#include "SphereCreator.h"
#include "nbSphere.h"
#include "Bandwidth.h"
#include "ChronoFactory.h"

using std::cout;
using std::endl;
using std::string;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

__global__ void kernelRaytacingGM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres);
__global__ void kernelRaytacingSM(uchar4* tabPixelsGM , uint w , uint h , float t , Sphere* tabSpheresGM , int nbSpheres);
__global__ void kernelRaytacingCM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres);
__global__ void kernelRaytacingCM2SM(uchar4* tabPixelsGM , uint w , uint h , float t , int nbSpheres);

__host__ void uploadToCM(Sphere* tabSpheres , int nbSpheres);

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

static string titre(const MemoryType& memoryType);

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructeur		*|
 \*-------------------------------------*/

Raytracing::Raytracing(const Grid& grid , uint w , uint h , float dt , bool isVerbose , int nbSpheres , const MemoryType& memoryType) :
	Animable_I<uchar4>(grid, w, h, titre(memoryType), isVerbose), // super classe
	memoryType(memoryType), //
	dt(dt), //
	nbSpheres(nbSpheres)
    {
    // Tools
    this->sizeSpheres = nbSpheres * sizeof(Sphere);
    this->t = 0;

    // spheres
	{
	Chrono* ptrChrono = ChronoFactory::create();
	SphereCreator sphereCreator(nbSpheres, w, h);
	ptrChrono->stop();
	if (isVerbose)
	    {
	    cout << "\n[SphereCreator] : " << *ptrChrono << endl;
	    }
	delete ptrChrono;

	uploadToDevice(sphereCreator.getTabSphere());
	} // SphereCreator depiler, donc detruit, tabSphere cote host detruit!
    }

Raytracing::~Raytracing()
    {
    // TODO Raytracing GPU MemoryManagement free
    switch (memoryType)
	{
    case GM:
	{
	GM::free(tabSpheresGM);

	break;
	}
    case CM:
	{
	// Indication: rien a detruire pour la CM
	// Note : la duree de vie pour la CM est une duree processus.

	break;
	}
    case SM:
	{
	// Indication: rien a detruire pour la SM
	// Note : la duree de vie pour la SM est une duree de vie de kernel, seulement!

	break;
	}
    case CM2SM:
	{
	// Indication: rien a detruire pour la SM et CM

	break;
	}
	}
    }

/*--------------------------------------*\
 |*		Methode			*|
 \*-------------------------------------*/

/**
 * Override
 */
void Raytracing::process(uchar4* tabPixelsGM , uint w , uint h , const DomaineMath& domaineMath)
    {

    switch (memoryType)
	{
    case GM:
	{
	kernelRaytacingGM<<<dg,db>>>(tabPixelsGM , w , h , t , tabSpheresGM , nbSpheres);
	// Call the kernel kernelRaytacingGM (prototype line 20, about)
	break;
	}
    case CM:
	{
	kernelRaytacingCM<<<dg,db>>>(tabPixelsGM , w , h , t, nbSpheres);
	break;
	}
    case SM:
	{
	size_t arraySphereSize = nbSpheres * sizeof(Sphere);
	kernelRaytacingSM<<<dg,db, arraySphereSize>>>(tabPixelsGM , w , h , t , tabSpheresGM , nbSpheres);
	break;
	}
    case CM2SM:
	{
	size_t arraySphereSize = nbSpheres * sizeof(Sphere);
	kernelRaytacingCM2SM<<<dg,db, arraySphereSize>>>(tabPixelsGM , w, h, t, nbSpheres);
	break;
	}
	}
    }

/**
 * Override
 */
void Raytracing::animationStep()
    {
    t += dt;
    }

/**
 * Override
 */
double Raytracing::getInputGO()
    {
    return NB_SPHERE * sizeof(Sphere) / ((double)1024 * (double)1024 * (double)1024);
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

void Raytracing::uploadToDevice(Sphere* tabSpheres)
    {
    Bandwidth bandwidth(sizeSpheres, "\n" + titre(memoryType) + " : Host -> Device :");

    switch (memoryType)
	{
    case GM:
	{
	// TODO Raytracing GM uploadToDevice
	// But : copier les spheres en GM
	// MM pout la GM ( malloc et memcpy)
	// Utiliser la classe GM
	// step 0
	GM::malloc(&tabSpheresGM, sizeSpheres); // pourquoi un adresse de pointeur
	GM::memcpyHToD(tabSpheresGM, tabSpheres, sizeSpheres);

	break;
	}
    case CM:
	{
	// TODO Raytracing CM uploadToDevice
	// But : copier les spheres en CM
	// Utiliser la methode importer uploadToCM et pister là!
	uploadToCM(tabSpheres , nbSpheres);

	break;
	}
    case SM:
	{
	// TODO Raytracing SM uploadToDevice

	// Indication:
	//		Coter device, on copie GM to SM
	//		Il faut donc d'abord copier les spheres sur le device!
	//		Le code est donc le meme que GM
	GM::malloc(&tabSpheresGM, sizeSpheres); // pourquoi un adresse de pointeur
	GM::memcpyHToD(tabSpheresGM, tabSpheres, sizeSpheres);

	break;
	}
    case CM2SM:
	{
	// Indication:
	//		Coter device, on copie CM to SM
	//		Il faut donc d'abord copier les spheres en CM
	//		Le code est donc le meme que CM
	uploadToCM(tabSpheres , nbSpheres);
	break;
	}
	}

    if (isVerbose)
	{
	cout << endl << bandwidth << endl;
	}
    }

string titre(const MemoryType& memoryType)
    {
    switch (memoryType)
	{
    case GM:
	return "Raytracing-GM-uchar4";

    case CM:
	return "Raytracing-CM-uchar4";

    case SM:
	return "Raytracing-SM-uchar4";

    case CM2SM:
	return "Raytracing-CM2SM-uchar4";

    default:
	{
	assert(false);
	return "ERROR";
	}
	}
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

