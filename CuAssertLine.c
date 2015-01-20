#include "CuTest_internal.h"

bool CuAssert_Line(CuTest* tc, const char* file, int line, const char* message, int condition)
{
	if (condition) return false;
	CuFail_Line(tc, file, line, message, NULL);
	return true;
}
