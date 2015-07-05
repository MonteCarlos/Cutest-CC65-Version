#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendFormat(CuString* str, const char* format, ...)
{
	va_list argp;
	char *buf;

	va_start(argp, format);
	//use (v)snprintf trick to determine number of characters to be printed, beforehand
	buf = (char*)CuAlloc( vsnprintf(NULL,0,format,argp) );
	assert (NULL != buf);
	vsprintf(buf, format, argp);
	va_end(argp);
	CuStringAppend(str, buf);

	CuFree(buf);
}
