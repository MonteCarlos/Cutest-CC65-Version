#include "CuTest_internal.h"

void CuSuiteInit(register CuSuite* testSuite)
{
	testSuite->testcount =
	testSuite->failCount =
	testSuite->totalcount =
	testSuite->suitecount =
	testSuite->isSubSuite =
	testSuite->ran = 0;
	testSuite->testlist = (CuTestPtr_t*)CuAlloc(CUTEST_LIST_STORAGERESERVE*sizeof(CuTestPtr_t));//alloc and zero fill

	assert (NULL != testSuite->testlist);
	testSuite->report = CuReportNew();
	//memset(testSuite->list, 0, sizeof(testSuite->list));
}
