
//#include <math.h>

#include "CutestString_internal.h"

// TODO (Stefan#1#): does not adjust str->length which maintains the length of the unallocated previous string
void CuStringResize(CuString* str, int newSize)
{
	assert(CuAlloc_getBufferValidity(str));
	assert(CuAlloc_getBufferValidity(CuStringCStr(str));
	//if newsize is smaller than old size, cut and terminate string so it matches into new buffer
	//important to use CuStringLen, because size is allocated in chunks of CUSTRING_LEN_NEW
	if (CuStringLen(str)+1 > newSize){
		str->length = newSize-1;
        CuStringCStr(str)[newSize-1] = '\0';//terminate cutted string
	}

	//reallocate memory for new size
	str->buffer = (char*) CuRealloc(CuStringCStr(str), sizeof(char) * newSize);
	assert(str->buffer != NULL);

	//update size
	str->size = newSize;
}
