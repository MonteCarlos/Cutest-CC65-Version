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
		//setup temporary string with is %format not %format content
		char *tempstr = CuStrFormat("is \"%s\" not \"%s\"", format, format);
		if (tempstr){
			va_list va;
			va_start(va,format);

			if ( CuStringAppendVariadicFormat(str, tempstr, va) ){
				returnVal = EXIT_SUCCESS;
			}
			//pass generated string (with doubled format string) to append function

			CuFree ((uint8_t*)tempstr);
			va_end(va);
		}
	}
	return returnVal;
}
