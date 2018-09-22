#include "CuTest_internal.h"

CuTest_t* CuTestNew(const char* name, TestFunction function)
{
	CuTest_t* tc = CU_ALLOC(CuTest_t);
	CuTestInit(tc, name, function);
	return tc;
}
