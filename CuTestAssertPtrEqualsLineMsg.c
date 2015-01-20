#include "CuTest_internal.h"

bool CuAssertPtrEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	void* expected, void* actual)
{
	char* buf = calloc(STRING_MAX, sizeof(char));
	assert (NULL != buf);
	if (expected == actual) return false;
	sprintf(buf, "expected pointer <0x%p> but was <0x%p>", expected, actual);
	CuFail_Line(tc, file, line, message, buf);
	assert (NULL != buf);
	free(buf);
	return true;
}
