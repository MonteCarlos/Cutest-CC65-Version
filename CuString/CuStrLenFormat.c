#include "CutestString_internal.h"

CuSize_t CuStrLenFormat(const char* const format, ...){
	va_list va;
	va_start(va, format);
	return CuStrGetVAExpandedFormatStringLength(format, va);
}
