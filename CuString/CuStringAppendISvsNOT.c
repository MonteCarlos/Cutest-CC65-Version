#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*	FUNCTION
	int CuStringAppendISvsNOT(CuString *str, const char* format,...)

Appends string for comparison of expected vs actual values.
Setups format string with both the same format for actual and expected values.
Passes the generated format string to CuStringAppendFormat so that
CuStringAppendISvsNOT also works for different input types specified by format string, too

in: CuString*, char, char* format
out: Cu_Error_t
*/

CuError_t CuStringAppendISvsNOT(CuString *str, const char* format,...){
	CuError_t returnVal = EXIT_FAILURE; //assume failure for security
    if (str){
        va_list va;
        va_start(va,format);

		CuStringAppend(str, "is: \"");
        CuStringAppendVariadicFormat(str, format, va);
        CuStringAppend(str, "\", not: \"");
        CuStringAppendVariadicFormat(str, format, va);
        CuStringAppend(str, "\"");

		va_end(va);
	}
	return returnVal;
}
