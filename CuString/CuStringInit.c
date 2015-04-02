
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"
void CuStringInit(register CuString* str)
{
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) CuAlloc(sizeof(char) * str->size);
	assert(str->buffer != NULL);
	str->buffer[0] = '\0';
}
