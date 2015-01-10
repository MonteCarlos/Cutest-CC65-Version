
#include "CuTest_internal.h"

void CuAssertIntEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	int expected, int actual)
{
	char* buf = (char*)calloc(STRING_MAX, sizeof(char));
	assert (NULL != buf);
	if (expected != actual){
		sprintf(buf, "expected <%d> but was <%d>", expected, actual);
		CuFail_Line(tc, file, line, message, buf);
	}
	free(buf);
}
