#include "CuTest_internal.h"

void CuSuiteInit(register CuSuite_t* testSuite)
{
	if (testSuite){
		testSuite->testcount =
		testSuite->failCount =
		testSuite->totalcount =
		testSuite->suitecount =
		testSuite->isSubSuite =
		testSuite->ran = 0;
		testSuite->testlist = (CuTestOrSuitePtr_t*)CuAlloc(CUTEST_LIST_STORAGERESERVE*sizeof(CuTestOrSuitePtr_t));//alloc and zero fill
		testSuite->name = CuStringNew();
		CuStringAppendFormat(testSuite->name, "%s%d", "Suite", testSuite->suitecount);
		assert (NULL != testSuite->testlist);
		testSuite->report = CuReportNew();
		//memset(testSuite->list, 0, sizeof(testSuite->list));
	}
}
