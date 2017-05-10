#include "CuTest_internal.h"
 CuSize_t CuTestFprintf(FILE* file, char* format, ...){
	va_list va;
 CuSize_t outputLength = 0;

	va_start(va, format);

	if (NULL != file){
		outputLength = vfprintf(file, format, va);
	}
	va_end(va);
	return outputLength;
}
