#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppend(CuString* str, const char* text)
{
	size_t length;
	assert(NULL != str);
	//assert(NULL != text);
	text = CuStrNULL(text); //replace with NULL if necessary

	if ( (length = CuStringLen(str) + strlen(text) + 1) >= CuStringSize(str)){
		CuStringResize(str, length+CUSTRING_LEN_INC);
		//always allocate a little more mem to reduce number of reallocs
	}

	strcat(CuStringCStr(str), text);
	str->length = strlen(CuStringCStr(str));
}
