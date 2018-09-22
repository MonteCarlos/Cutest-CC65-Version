#include "CuTest_internal.h"

bool CuAssert_Line(CuTest_t* tc, const char* file, unsigned long int line, const char* message, int condition)
{
	if (tc){
		++tc->assertCnt;

		if (condition) return false;
		CuFail_Line(tc, file, line, message, NULL);
		return true;
	}
	return false;
}
