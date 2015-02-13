#include "CuTest_internal.h"

size_t CuSuiteGetFailcount(CuSuite* testSuite)
{
	return testSuite->failCount;
}

