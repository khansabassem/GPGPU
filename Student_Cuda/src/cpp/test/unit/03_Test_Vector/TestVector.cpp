#include "TestVector.h"

#include "Hardware.h"
#include "ChronoFactory.h"
#include "Limits.h"

#include "AddVectorProviderBig.h"

using std::cout;
using std::endl;


/*----------------------------------------------------------------------*\
 |*			Implementation 					*|
 \*---------------------------------------------------------------------*/

/*--------------------------------------*\
 |*		Constructor		*|
 \*-------------------------------------*/

TestVector::TestVector() : //
	TestCuda(new AddVectorProviderBig())
    {
    enableTestMonoThread(true);
    enableTestMonoBlock(true);
    enableTestPerformance(true, thresholdPerformanceFps());
    }

/*--------------------------------------*\
 |*		Methodes		*|
 \*-------------------------------------*/

/**
 * Override
 */
void TestVector::allTests()
    {
    TestCuda::allTests();

    TEST_ADD(TestVector::testSpecial);
    }

/**
 * si on le met pas probleme de title dans le html (workaround for this, le test en soi n'est pas important
 */
void TestVector::testSpecial()
    {
    showTitle("Test special #thread=#core");

    const int MP = Hardware::getMPCount();
    const int CORE_MP = Hardware::getCoreCountMP();

    dim3 dg(MP, 1, 1);
    dim3 db(CORE_MP, 1, 1);
    Grid grid(dg, db);

    test(grid);
    }

/*--------------------------------------*\
 |*		private		*|
 \*-------------------------------------*/

/**
 * static
 */
long TestVector::thresholdPerformanceFps()
    {
    return 400; // cbi naif 470 (avec MM)
    // return 18000; // cbi naif 19916 (sans MM)
    }

/*----------------------------------------------------------------------*\
 |*			End	 					*|
 \*---------------------------------------------------------------------*/

