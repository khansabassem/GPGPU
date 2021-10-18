#pragma once

#include "Thread1D.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

class ReductionAdd
    {
    public:

	/**
	 * Hypothese:
	 *
	 * 	(H1) 	On suppose que T est un type simple sur lequel atomicAdd existe
	 *
	 * Exemple :
	 * 		ReductionAdd::reduce(tabSm,ptrDevResultatGM);
	 *
	 * Contraintes :
	 *
	 * 	(C1) 	|tabSM| puissance de 2, comme 2,4,8,16,32,64,128,256,512,1024
	 * 	(C2)	|ThreadByBlock|=|tabSM|
	 * 	(C3)	Reduction intra-thread laisser a l'utilsiateur (ie remplissage de tabSM)
	 * 	(C4)	Grid 1D
	 *
	 * Warning :
	 *
	 * 	(W1)	ptrResultGM n'est pas un tableau, mais un scalaire contenant le resultat final
	 * 	(W2)	Oubliez pas le MM pour  ptrResultGM
	 * 	(W3)	Oubliez pas l'initialisation de ptrResultGM
	 * 		Exemples :
	 * 			adition 	: a zero avec un Device::memclear(...)
	 * 			multiplication  : a 1 avec un Device:memcpyHtoD(...)
	 */
	template <typename T>
	static __device__ void reduce(T* tabSM, T* ptrResultGM)
	    {
	    // Rappel :
	    // 		|ThreadByBlock|=|tabSM| .
	    // 		Il y autant de case en SM que de thread par block.
	    //		Chaque thread possede son armoire en SM
	    //		1 thread <---> 1 armoire
	    reductionIntraBlock(tabSM);
	    reductionInterBlock(tabSM, ptrResultGM);
	    // __syncthreads();// pour touts les threads d'un meme block, necessaires? ou?
	    // deja fait dans l ecrasement
	    }

    private:

	/*--------------------------------------*\
	|*	reductionIntraBlock		*|
	 \*-------------------------------------*/

	/**
	 * used dans une boucle in reductionIntraBlock
	 */
	template <typename T>
	static __device__ void ecrasement(T* tabSM, int middle)
	    {
	    //const int TID_LOCAL = Thread1D::tidLocal();
	    const int TID_LOCAL = threadIdx.x;
	    if(TID_LOCAL < middle)
		{
		tabSM[TID_LOCAL] += tabSM[TID_LOCAL+middle];
		}
	    // Indication :
	    //	(I1) je suis un thread, je dois faire quoi ?
	    // 	(I2) Tous les threads doivent-ils faire quelquechose?
	    // __syncthreads();// pour touts les threads d'un meme block, necessaires? ou?
	    // Non, car deja fait lors de l ecrasement
	    }

	/**
	 * Sur place, le resultat est dans tabSM[0]
	 */
	template <typename T>
	static __device__ void reductionIntraBlock(T* tabSM)
	    {
	    // Ecrasement sucessifs dans une boucle (utiliser la methode ecrasement ci-dessus)
	    int middle = Thread1D::nbThreadBlock() >> 1;
	    while(middle > 0)
		{
		ecrasement(tabSM, middle);
		middle = middle>>1;
		// ne jamais mettre de syncthreads dans un if
		__syncthreads();// pour touts les threads d'un meme block
		}

	    }

	/*--------------------------------------*\
	|*	reductionInterblock		*|
	 \*-------------------------------------*/

	template <typename T>
	static __device__ void reductionInterBlock(T* tabSM, T* ptrResultGM)
	    {
	    //const int TID_LOCAL = Thread1D::tidLocal();
	    const int TID_LOCAL = threadIdx.x;
	    if(TID_LOCAL == 0)
		{
		atomicAdd(ptrResultGM,tabSM[0]);
		}
	    // pas de syncthreads

	    // __syncthreads();// pour touts les threads d'un meme block, necessaires? ou?
	    }

    };

/*----------------------------------------------------------------------*\
|*			End	 					*|
 \*---------------------------------------------------------------------*/
