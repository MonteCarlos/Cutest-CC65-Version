#include "CuTest_internal.h"

bool CuAssertStrEquals_LineMsg(CuTest* tc, const char* file, int line, const char* message,
	const char* expected, const char* actual)
{
	//CuString *string = CuStringNew();
	if ((expected == NULL && actual == NULL) ||
	    (expected != NULL && actual != NULL &&
	     strcmp(expected, actual) == 0))
	{
		return false;
	}

	CuFail_Line(tc, file, line, message, " ");
	//CuStringAppend(tc->message, ", ");
    CuStringAppendISvsNOT(tc->message, "%s", expected, actual);

	return true;
}
