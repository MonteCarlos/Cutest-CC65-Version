#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*	FUNCTION
	CuErrot_t CuStringAppendLineFile(CuString* str, char* file, unsigned long int line)

Appends string for comparison of expected vs actual values.
Setups format string with both the same format for actual and expected values.
Passes the generated format string to CuStringAppendFormat so that
CuStringAppendISvsNOT also works for different input types specified by format string, too

in: CuString*, char, char* format
out: Cu_Error_t
*/

//Use long for line number to be not limited to 65535 lines per file
CuError_t CuStringAppendLineFile(CuString* str, char* file, unsigned long int line){
	//CuStringAppendFormat already checks str
	return CuStringAppendFormat(str,"%s (%lu)", file, line);
}
