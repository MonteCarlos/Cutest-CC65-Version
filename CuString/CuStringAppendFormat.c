#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendFormat(CuString* str, const char* format, ...)
{
	va_list argp;
	char *buf = (char*)calloc(HUGE_STRING_LEN, sizeof(char));
	assert (NULL != buf);
	va_start(argp, format);
	vsprintf(buf, format, argp);
	va_end(argp);
	CuStringAppend(str, buf);
	assert(NULL != buf);
	free(buf);
}
