#include "CuTest_internal.h"

size_t CuTestFprintf(FILE* file, char* format, ...){
	va_list va;
	size_t outputLength = 0;

	va_start(va, format);

	if (NULL != file){
		outputLength = vfprintf(file, format, va);
	}
	va_end(va);
	return outputLength;
}
