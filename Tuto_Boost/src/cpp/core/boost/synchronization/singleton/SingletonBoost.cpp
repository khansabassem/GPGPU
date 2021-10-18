#include "SingletonBoost.h"

#include <iostream>
#include <assert.h>

using boost::mutex;
using std::cout;
using std::endl;
using std::string;

using boost::this_thread::get_id;

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		constructeur		*|
 \*-------------------------------------*/

SingletonBoost::SingletonBoost()
    {
    cout << "[SingletonBoost] :: create" << endl;

    SingletonBoost::compteur++;
    assert(SingletonBoost::compteur == 1);
    }

/*--------------------------------------*\
|*		methode			*|
 \*-------------------------------------*/

void SingletonBoost::print_tid()
    {
    cout << "[" << something << "] " << get_id() << endl;
    }

/*--------------------*\
 |*	static	       *|
 \*-------------------*/

/**
 * static
 */
SingletonBoost* SingletonBoost::getInstance()
    {
    mutex.lock();
	{
	if (instance == NULL)
	    {
	    assert(something != "NOT_DEFINE");

	    instance = new SingletonBoost();
	    }
	}

    mutex.unlock();

    return instance;
    }

/**
 * static
 */
void SingletonBoost::init(string something)
    {
    mutex.lock();
	{
	assert(instance == NULL);
	SingletonBoost::something = something;
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
string SingletonBoost::something = "NOT_DEFINE";

/**
 * static
 */
int SingletonBoost::compteur = 0;

/*--------------------*\
 |*  static  Tools    *|
 \*-------------------*/

/**
 * static
 */
mutex SingletonBoost::mutex;

/**
 * static
 */
SingletonBoost *SingletonBoost::instance = NULL;

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
