#pragma once

#include <mutex>
#include <iostream>

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

class SingletonStd
    {
	/*--------------------*\
	|*	Constructeur  *|
	 \*-------------------*/

    private:

	SingletonStd();

	/*--------------------*\
	|*	Methodes	*|
	 \*-------------------*/

    public:

	void print_tid();

	/*--------------------*\
	|*	static	       *|
	 \*-------------------*/

	/**
	 * Call once init before getInstance
	 */
	static SingletonStd* getInstance();

	/**
	 * Call once init before getInstance
	 * Not always required, can be remove if not usefull
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

	static std::mutex mutex;

	static SingletonStd* instance;

    };

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/
