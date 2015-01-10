#include "CuTest_internal.h"

void CuSuiteSummary(CuSuite* testSuite, CuString* summary)
{
	int i;
	for (i = 0 ; i < testSuite->count ; ++i)
	{
		CuTest* testCase = testSuite->list[i];
		CuStringAppend(summary, testCase->failed ? "F" : ".");
	}
	CuStringAppend(summary, "\n\n");
}
