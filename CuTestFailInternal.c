#include "CuTest_internal.h"


void CuFailInternal(CuTest* tc, const char* file, int line, CuString* string)
{
	char* buf = (char*)CuAlloc(HUGE_STRING_LEN*sizeof(char));
	assert (NULL != buf);
	sprintf(buf, "%s:%d: ", file, line);
	CuStringInsert(string, buf, 0);//buf is appended to string.

	//buf is not needed anymore
	CuFree(buf);

	tc->failed = 1;
	tc->message = string;

	//if (tc->jumpBuf != 0) longjmp(tc->jumpBuf[0], 0); //This breaks execution on true

	//This part is only reached if jumpBuf == NULL
}
