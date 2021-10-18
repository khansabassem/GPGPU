#include "SingletonStd.h"

#include <iostream>
#include <assert.h>
#include <thread>

using std::mutex;
using std::cout;
using std::endl;
using std::string;

using std::this_thread::get_id;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		constructeur		*|
 \*-------------------------------------*/

SingletonStd::SingletonStd()
    {
    cout << "[SingletonStd] :: create" << endl;

    SingletonStd::compteur++;
    assert(SingletonStd::compteur == 1);
    }

/*--------------------------------------*\
|*		methode			*|
 \*-------------------------------------*/

void SingletonStd::print_tid()
    {
    cout << "[" << something << "] " << get_id() << endl;
    }

/*--------------------*\
 |*	static	       *|
 \*-------------------*/

/**
 * static
 */
SingletonStd* SingletonStd::getInstance()
    {
    mutex.lock();
	{
	if (instance == NULL)
	    {
	    assert(something != "NOT_DEFINE");

	    instance = new SingletonStd();
	    }
	}

    mutex.unlock();

    return instance;
    }

/**
 * static
 */
void SingletonStd::init(string something)
    {
    mutex.lock();
	{
	assert(instance == NULL);
	SingletonStd::something = something;
	}
    mutex.unlock();
    }

/*--------------------------------------*\
|*		attribut		*|
 \*-------------------------------------*/

/*--------------------*\
 |*  static  Data    *|
 \*-------------------*/

/**
 * static
 */
string SingletonStd::something = "NOT_DEFINE";

/**
 * static
 */
int SingletonStd::compteur = 0;

/*--------------------*\
 |*  static  Tools    *|
 \*-------------------*/

/**
 * static
 */
mutex SingletonStd::mutex;

/**
 * static
 */
SingletonStd *SingletonStd::instance = NULL;



/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
