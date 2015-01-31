#include "CuTest_internal.h"

void CuSuiteRun(CuSuite* testSuite)
{
	int i;
	unsigned long int pendingfrees;
	CuTest* testCase = NULL;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		printf("%d:",i);
		testCase = testSuite->list[i];
		fputs(testCase->name, stdout);

		pendingfrees = CuAlloc_getPendingFrees();
		CuTestRun(testCase);
		assert ( pendingfrees = CuAlloc_getPendingFrees());
		if (testCase->failed) {
			puts("->FAILED");
			testSuite->failCount += 1;
		}else{
			puts("->OK");
		}
	}
}
