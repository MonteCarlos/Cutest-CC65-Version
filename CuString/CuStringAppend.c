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

	if (CuStringLen(str) + (length=strlen(text) + 1) >= str->size)
		CuStringResize(str, CuStringLen(str) + length /*+ STRING_INC*/);
	str->length += length;
	strcat(CuStringCStr(str), text);
}
