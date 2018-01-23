#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/* appends string to CuString using format specifier and va args
	If str == NULL, a new CuString is created with the appropriate content and returned to the caller
*/
CuString *CuStringAppendVariadicFormat(CuString* str, const char* format, va_list va)
{
	char *buf = CuStrVaFormat(format, va);
	CuString *str2 = NULL;
	assert (NULL != buf);
    //Using str2 here is OK, as CuStringAppend eventually creates new CuString if str is NULL
	str2 = CuStringAppend(str, buf);

	CuFree(buf);
	return str2;
}
