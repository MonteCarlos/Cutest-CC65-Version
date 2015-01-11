#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

// TODO (Stefan#1#): does not adjust str->length which maintains the length of the unallocated previous string
void CuStringResize(CuString* str, int newSize)
{
	str->buffer = (char*) realloc(str->buffer, sizeof(char) * newSize);
	assert(str->buffer != NULL);
	str->size = newSize;
}
