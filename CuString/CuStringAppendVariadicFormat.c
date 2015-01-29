#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendVariadicFormat(CuString* str, const char* format, va_list va)
{
	char *buf = (char*)calloc(HUGE_STRING_LEN, sizeof(char));
	assert (NULL != buf);
	//va_start(va, format);
	vsprintf(buf, format, va);
	//va_end(va);
	CuStringAppend(str, buf);

	free(buf);
}
