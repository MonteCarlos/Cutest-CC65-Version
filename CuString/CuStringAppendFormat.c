#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendFormat(CuString* str, const char* format, ...)
{
	va_list argp;
	va_start(argp, format);
	CuStringAppendVariadicFormat(str, format, argp);

	va_end(argp);

}
