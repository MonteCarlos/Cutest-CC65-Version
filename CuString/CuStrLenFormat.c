#include "CutestString_internal.h"

size_t CuStrLenFormat(const char* const format, ...){
	va_list va;
	va_start(va, format);
	return CuStrLenVaFormat(format, va);
}
