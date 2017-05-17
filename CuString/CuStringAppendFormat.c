#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*	Function CuStringAppendFormat

Appends String to CuString according to format and va_args

in: CuString*, char* format, va_args
out: Cu_Error_t
*/

CuError_t CuStringAppendFormat(CuString* str, const char* format, ...)
{
	if (str){
		va_list argp;
		va_start(argp, format);
		CuStringAppendVariadicFormat(str, format, argp);

		va_end(argp);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
