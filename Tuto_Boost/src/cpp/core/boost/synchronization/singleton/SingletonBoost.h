#pragma once

#include <boost/thread.hpp>
#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class SingletonBoost
    {
	/*--------------------*\
	|*	Constructeur  *|
	 \*-------------------*/

    private:

	SingletonBoost();

	/*--------------------*\
	|*	Methode  	*|
	 \*-------------------*/

    public:

	void print_tid();

	/*--------------------*\
	 |*	static	       *|
	 \*-------------------*/

	/**
	 * Call once init before getInstance
	 */
	static SingletonBoost* getInstance();

	/**
	 * Call once init before getInstance
	 * Not always required, can be remove if  not usefull
	 */
	static void init(std::string something); // exemmple avec string

    private:

	/*--------------------*\
	 |*	Attribut       *|
	 \*-------------------*/

	// Data
	static std::string something; // un truc utile pour la classe

	static int compteur;

	// Tools

	static boost::mutex mutex;

	static SingletonBoost* instance;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
