#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*	Function CuStringAppendChar

Appends char to CuString

in: CuString*, char
out: Cu_Error_t
*/

CuError_t CuStringAppendChar(CuString* str, char ch)
{
	if (str){
		//buffer to convert char into string to use with CuStringAppend
		char text[2]={};
		//Only append, if char is not \0
		if ('\0' != ch){
			text[0] = ch;
			CuStringAppend(str, text);
			return EXIT_SUCCESS;
		}
	}
	return EXIT_FAILURE;
}
