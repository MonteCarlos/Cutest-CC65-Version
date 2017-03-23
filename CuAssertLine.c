#include "CuTest_internal.h"

bool CuAssert_Line(CuTest* tc, const char* file, unsigned int line, const char* message, int condition)
{
	if (condition) return false;
	++tc->assertCnt;
	CuFail_Line(tc, file, line, message, NULL);
	return true;
}
