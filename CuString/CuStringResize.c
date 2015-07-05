
//#include <math.h>

#include "CutestString_internal.h"

// TODO (Stefan#1#): does not adjust str->length which maintains the length of the unallocated previous string
void CuStringResize(register CuString* str, int newSize)
{
	str->buffer = (char*) CuRealloc(str->buffer, sizeof(char) * newSize);
	assert(str->buffer != NULL);
	str->size = newSize;
}
