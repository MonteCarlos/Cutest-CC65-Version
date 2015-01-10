#include "CuTest_internal.h"


void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2)
{
	int i;
	for (i = 0 ; i < testSuite2->count ; ++i)
	{
		CuTest* testCase = testSuite2->list[i];
		CuSuiteAdd(testSuite, testCase);
	}
}
