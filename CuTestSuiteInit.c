#include "CuTest_internal.h"

void CuSuiteInit(CuSuite* testSuite)
{
	testSuite->testcount = 0;
	testSuite->failCount = 0;
	testSuite->testlist = (CuTest**)CuAlloc(CUTEST_LIST_STORAGERESERVE*sizeof(CuTest*));//alloc and zero fill

	assert (NULL != testSuite->testlist);
	testSuite->report = CuReportNew();
	//memset(testSuite->list, 0, sizeof(testSuite->list));
}
