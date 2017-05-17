/*
	CuStringAppend
	Appends c_str to CuString

	input:
		CuString: String which should be extended
		c_str:	text to append
	output:
		CuString with appended c_str or new CuString with content from text parameter
*/

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "CutestString_internal.h"

CuString *CuStringAppend(CuString* str, const char* text)
{
	CuSize_t length;
	//assert(NULL != str);

	//if invalid pointer given, create new CuString
	if (NULL == str){
		str = CuStringNew();
	}
	//assert(NULL != text);
	text = CuStrNULL(text); //replace with NULL if necessary

	if ( (length = CuStringLen(str) + strlen(text) + 1) >= CuStringSize(str)){
		CuStringResize(str, length+CUSTRING_LEN_INC);
		//always allocate a little more mem to reduce number of reallocs
	}

	strcat(CuStringCStr(str), text);
	str->length = strlen(CuStringCStr(str));

	//As this functions possibly creates new string, return the pointer to the CuStering
	return str;
}
