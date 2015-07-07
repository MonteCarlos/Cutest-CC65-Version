#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppend(register CuString* str, const char* text)
{
	size_t length;

	if (text == NULL) {
		text = "NULL";
	}

	if ( (length = CuStringLen(str) + strlen(text) + 1) >= CuStringSize(str)){
		CuStringResize(str, length);
	}

	strcat(CuStringCStr(str), text);
	str->length = strlen(CuStringCStr(str));
}
