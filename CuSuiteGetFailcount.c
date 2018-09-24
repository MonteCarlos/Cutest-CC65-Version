#include "CuTest_internal.h"
CuSize_t CuSuiteGetFailcount (CuSuite_t *testSuite) {
    if (testSuite) return testSuite->failCount;

    return ~0;
}

