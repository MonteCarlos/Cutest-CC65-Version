#include "CuTest_internal.h"

bool CuAssertLongEquals_LineMsg(CuTest_t* tc, const char* file, unsigned int line, const char* message,
	long expected, long actual)
{
	//char* buf = (char*)calloc(STRING_MAX, sizeof(char));
	//assert (NULL != buf);
	if (expected != actual){
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

