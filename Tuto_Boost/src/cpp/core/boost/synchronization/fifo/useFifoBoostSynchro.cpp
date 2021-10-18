
#include <iostream>
#include <unistd.h>
#include "limits.h"

#include <boost/lockfree/spsc_queue.hpp>
#include <boost/atomic.hpp>

using std::cout;
using std::endl;

// spsc = single-producer/single-consumer queue (commonly known as ringbuffer)
#ifndef FifoInt
#define FifoInt boost::lockfree::spsc_queue<int>
#endif

#ifndef AtomicBool
#define AtomicBool boost::atomic<bool>
#endif

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/


/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useFifoBoostSynchro(void);


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useFifoBoostSynchro(void)
    {
    cout << endl << "[Use Boost FIFO Synchro] : " << endl << endl;

    const int N = INT_MAX/5;
    FifoInt fifo(N); // input fifo = taille minimal que va prendre en mémoire la fifo

    AtomicBool done(false);

    #pragma omp parallel sections
	{
	#pragma omp section // producteur -> 1 2 3 . . . N
	    {
	    cout<<"\nProducteur starting ..."<<endl<<endl;

	    for (int i = 1; i <= N; ++i)
		{
		//cout << "push " << i << endl;

		fifo.push(i);

		//cout<<"fifo size : "<<fifo.read_available()<<endl;
		// usleep(1);// [ms]
		}

	    done=true;
	    cout<<"\nProducteur end:"<<endl<<endl;
	    }

	#pragma omp section // consomateur
	    {
	    cout<<"\nConsomateur starting ..."<<endl<<endl;

	    int i;
	    int old = 0;

	    while(!done) // tant que le poducteur n'a pas finit on boucle
		{
		while (fifo.pop(i))// pop renvoie false si vide
		    {
		    //cout << "pop " << i << endl;

		    assert(i == old + 1);
		    old = i;

		   // cout<<"fifo size : "<<fifo.read_available()<<endl;
		   //usleep(1);// [ms]
		    }
		}

	    assert(old==N);

	    cout<<"Consomateur end"<<endl<<endl;
	    }

	}

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

