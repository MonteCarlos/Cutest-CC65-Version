#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*-------------------------------------------------------------------------*
 * CuStr
 *-------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------*
 * CuString
 *-------------------------------------------------------------------------*/

















#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"







CuError_t CuStringInsert(CuString* str, const char* text, int pos)
{
	if (str){
		int length = strlen(text);
		if (pos > str->length)
			pos = str->length;
		if (str->length + length + 1 >= str->size)
			CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
		memmove(str->buffer + pos + length, str->buffer + pos, (str->length - pos) + 1);
		str->length += length;
		memcpy(str->buffer + pos, text, length);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

