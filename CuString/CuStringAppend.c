#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

void CuStringAppend(register CuString* str, const char* text)
{
	int length = strlen(text);

	if (text == NULL) {
		text = "NULL";
	}

	if (str->length + length + 1 >= str->size)
		CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
	str->length += length;
	strcat(str->buffer, text);
}
