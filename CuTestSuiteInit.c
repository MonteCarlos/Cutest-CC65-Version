#include "CuTest_internal.h"

void CuSuiteInit(CuSuite* testSuite)
{
	testSuite->count = 0;
	testSuite->failCount = 0;
	testSuite->testlist = (CuTest**)CuAlloc(CUTEST_LIST_STORAGERESERVE*sizeof(CuTest*));//alloc and zero fill
	testSuite->suitelist = (CuTest**)CuAlloc(CUSUITE_LIST_STORAGERESERVE*sizeof(CuSuite*));//alloc and zero fill

	assert (NULL != testSuite->list);
	testSuite->report = CuReportNew();
	//memset(testSuite->list, 0, sizeof(testSuite->list));
}
