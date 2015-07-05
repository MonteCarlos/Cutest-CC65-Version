#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppendVariadicFormat(CuString* str, const char* format, va_list va)
{
	char *buf = CuStrVaFormat(format, va);
	assert (NULL != buf);

	CuStringAppend(str, buf);

	CuFree(buf);
}
