#include "CutestString_internal.h"

size_t CuStrLenFormat(char* format, ...){
	va_list va;
	char discard;
	va_start(va, format);
	return vsnprintf(&discard, 1, format, va);
}
