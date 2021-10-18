#include "TestCalculatriceFloat.h"

/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
|*		Constructeur		*|
 \*-------------------------------------*/

TestCalculatriceFloat::TestCalculatriceFloat(void)
    {
    TEST_ADD(TestCalculatriceFloat::testAddition);
    TEST_ADD(TestCalculatriceFloat::testFois);
    }

/*--------------------------------------*\
|*		Methodes		*|
 \*-------------------------------------*/

void TestCalculatriceFloat::testAddition(void)
    {
    TEST_ASSERT(CalculatriceFloat::sum(2, 3) == 5);
    TEST_ASSERT(CalculatriceFloat::sum(-2, 3) == 1.0);
    }

void TestCalculatriceFloat::testFois(void)
    {
    TEST_ASSERT(CalculatriceFloat::fois(2, 3) == 6);
    TEST_ASSERT(CalculatriceFloat::fois(-2, 3) == -6);
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

