#include "CuTest_internal.h"

// TODO (MyAcer#1#): Suite should not incorporate test from other suite because it causes dealloc problems when two suites are deleted having some tests in common
void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2)
{
	//int i;
CuSize_ttestcount = testSuite->totalcount;
   CuSize_tresidualBytesToNextAlloc = CUTEST_LIST_STORAGERESERVE-testcount % CUTEST_LIST_STORAGERESERVE;
    register CuTestPtr_t* testlist = testSuite->testlist;

	if ( residualBytesToNextAlloc  == 1 ){
        testlist = CuRealloc(testlist, (testcount+1+CUTEST_LIST_STORAGERESERVE)*sizeof(CuTestPtr_t));
        testSuite->testlist = testlist;
	}
	testlist[testcount].suite = testSuite2;
	testlist[testcount].isSuite = true;

	testSuite->suitecount += 1;
	testSuite->totalcount +=1;

	testSuite2->isSubSuite = true;
	/*for (i = 0 ; i < testSuite2->count ; ++i)
	{
		CuSuiteAdd(testSuite, testSuite2->list[i]);
	}*/
}
