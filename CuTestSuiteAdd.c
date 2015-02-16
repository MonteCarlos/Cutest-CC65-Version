#include "CuTest_internal.h"

void CuSuiteAdd(CuSuite* testSuite, CuTest *testCase)
{
    size_t testcount;

	if ( (testcount = testSuite->count)%CUTEST_LIST_STORAGERESERVE == (CUTEST_LIST_STORAGERESERVE-1) ){
        testSuite->testlist = CuRealloc(testSuite->testlist, testcount+1+CUTEST_LIST_STORAGERESERVE);
	} testSuite->list[(testSuite->count)++] = testCase;
	//++testSuite->count;
}
