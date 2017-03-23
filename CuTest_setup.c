#include "CuTest_internal.h"

CuTest* CuTestSetup(const char* name, TestFunction function, CuTest_SetupFnc_t *setup, CuTest_TeardownFnc_t *teardown, ...)
{
    CuTest* tc = CU_ALLOC(CuTest);
	va_list va;
    va_start(va, teardown);

	CuTestInit(tc, name, function);
    tc->setup = setup;
    tc->teardown = teardown;
    //tc->vaargs1 = va_copy(va);
	return tc;
}

