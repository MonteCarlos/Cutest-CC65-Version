#include "CuTest_internal.h"
CuSize_t CuSuiteGetFailcount(CuSuite* testSuite)
{
	if (testSuite) return testSuite->failCount;
	return ~0;
}

