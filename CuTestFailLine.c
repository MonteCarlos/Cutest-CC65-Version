#include "CuTest_internal.h"

void CuFail_Line(CuTest* tc, const char* file, int line, const char* message, const char* message2)
{
	//CuString *string = CuStringNew();

	//CuStringInit(&string);
	if ( 0 != CuStringlen(tc->message) ) {
        CuStringAppendChar(tc->message,'\n');
	}
	CuTestGenerateMessage(tc->message, message, message2, file, line);
	tc->failed = 1;
	//tc->message = string;
	/*if (message2 != NULL)
	{
		CuStringAppend(&string, message2);
		CuStringAppend(&string, ": ");
	}
	CuStringAppend(&string, message);*/
	//CuFailInternal(tc, file, line, &string);
}
