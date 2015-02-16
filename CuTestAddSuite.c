#include "CuTest_internal.h"

// TODO (MyAcer#1#): Suite should not incorporate test from other suite because it causes dealloc problems when two suites are deleted having some tests in common
void CuSuiteAddSuite(CuSuite* testSuite, CuSuite* testSuite2)
{
	//int i;
	testSuite -> suitelist[suitecount++] = testSuite2;
	/*for (i = 0 ; i < testSuite2->count ; ++i)
	{
		CuSuiteAdd(testSuite, testSuite2->list[i]);
	}*/
}
