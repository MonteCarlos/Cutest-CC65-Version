#include "CuTest_internal.h"

void CuSuiteInit(CuSuite* testSuite)
{
	testSuite->count = 0;
	testSuite->failCount = 0;
	testSuite->list = (CuTest**)calloc(MAX_TEST_CASES, sizeof(CuTest*));//alloc and zero fill
	assert (NULL != testSuite->list);
	//memset(testSuite->list, 0, sizeof(testSuite->list));
}
