#include "CuTest_internal.h"

bool CuAssertPtrEquals_LineMsg(CuTest* tc, const char* file, unsigned int line, const char* message,
	const void* expected, const void* actual)
{
	//char* buf = CuAlloc(STRING_MAX*sizeof(char));
//	assert (NULL != buf);
	if (expected == actual) return false;
	CuFail_Line(tc, file, line, message, " ");
	//CuStringAppend(tc->message, ": ");
	CuStringAppendISvsNOT(tc->message, "%p", expected, actual);
	//sprintf(buf, "expected pointer <0x%p> but was <0x%p>", expected, actual);
	//CuFail_Line(tc, file, line, message, buf);
	//assert (NULL != buf);
	//CuFree(buf);
	return true;
}
