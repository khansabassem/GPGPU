#include <iostream>
#include <stdlib.h>

using std::cout;
using std::endl;

/*----------------------------------------------------------------------*\
 |*			Declaration 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Imported	 	*|
 \*-------------------------------------*/

extern void helloThread_Procedure(void);
extern void helloThread_ProcedureArgs(void);
extern void helloThread_Objet(void);
extern void helloThread_Methode(void);

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useThread(void);


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Public			*|
 \*-------------------------------------*/

bool useThread(void)
    {
    cout<<"[Use Boost Thread] : "<<endl;

    helloThread_Procedure();
    helloThread_ProcedureArgs();
    helloThread_Objet();
    helloThread_Methode();

    return true;
    }

/*--------------------------------------*\
 |*		Private			*|
 \*-------------------------------------*/

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

