#include "CutestString_internal.h"

size_t CuStrLenVaFormat(const char* const format, va_list va){
	char discard;

	return vsnprintf(&discard, 1, format, va);
}

