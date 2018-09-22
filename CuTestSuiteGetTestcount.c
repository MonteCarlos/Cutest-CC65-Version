#include "CuTest_internal.h"

CuSize_t CuSuiteGetTestcount(CuSuite_t* testSuite)
{
	if (testSuite) return testSuite->testcount;
	return ~0;
}


