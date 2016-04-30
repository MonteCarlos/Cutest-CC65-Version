
#include "CuTest_internal.h"

bool CuAssertGeneralEquals_LineMsg(CuTest* tc, const char* file, unsigned int line, const char* message,
	void *expected, void *actual, bool (*cmpFnc)(void* a, void *b))
{
	//char* buf = (char*)calloc(STRING_MAX, sizeof(char));
	//assert (NULL != buf);
	if (!cmpfnc(a,b)){
		//sprintf(buf, "expected <%d> but was <%d>", expected, actual);
		CuFail_Line(tc, file, line, message, " ");
		//CuStringAppend(tc->message, ": ");

		//here axctual and expected are exchanged which is reasoned in the va macros used in more deeply nested function
        CuStringAppendISvsNOT(tc->message, "%d", actual, expected);
		return true;
	}
	//free(buf);
	return false;
}
