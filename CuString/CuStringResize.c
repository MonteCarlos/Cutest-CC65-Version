
//#include <math.h>

#include "CutestString_internal.h"

// TODO (Stefan#1#): does not adjust str->length which maintains the length of the unallocated previous string
void CuStringResize(CuString* str, int newSize)
{
	//reallocate memory for new size
	str->buffer = (char*) CuRealloc(str->buffer, sizeof(char) * newSize);
	assert(str->buffer != NULL);
	//if newsize is smaller than old size, cut and terminate string so it matches into new buffer
	if (CuStringSize(str) > newSize){
		CuStringCStr(str)[newSize-1] = '\0';
		str->length = newSize-1;
	}
	str->size = newSize;
}
