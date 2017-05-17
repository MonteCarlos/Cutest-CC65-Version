#include "CuTest_internal.h"

bool CuSuiteAdd(CuSuite* testSuite, CuTest *newtest)
{
    if (testSuite){
		if (newtest){
			CuSize_t testcount = testSuite->testcount;
			CuSize_t residualBytesToNextAlloc = CUTEST_LIST_STORAGERESERVE-testcount % CUTEST_LIST_STORAGERESERVE;
			register CuTestPtr_t *testlist = testSuite->testlist;

			if ( residualBytesToNextAlloc  == 1 ){
				testlist = CuRealloc(testlist, (testcount+1+CUTEST_LIST_STORAGERESERVE)*sizeof(CuTestPtr_t));
			}
			testlist[testcount].test = newtest;
			testlist[testcount].isSuite = false;
			testSuite->testcount+=1;
			testSuite->totalcount+=1;
			testSuite->testlist = testlist;
			//++testSuite->count;

			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
