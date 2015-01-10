#include "CuTest_internal.h"

void CuSuiteRun(CuSuite* testSuite)
{
	int i;
	CuTest* testCase = NULL;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		printf("%d:",i);
		testCase = testSuite->list[i];
		fputs(testCase->name, stdout);
		CuTestRun(testCase);
		if (testCase->failed) {
			puts("->FAILED");
			testSuite->failCount += 1;
		}else{
			puts("->OK");
		}
	}
}
