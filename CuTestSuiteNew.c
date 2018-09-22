#include "CuTest_internal.h"

CuSuite_t* CuSuiteNew(void)
{
	CuSuite_t* testSuite = CU_ALLOC(CuSuite_t);
	CuSuiteInit(testSuite);
	return testSuite;
}
