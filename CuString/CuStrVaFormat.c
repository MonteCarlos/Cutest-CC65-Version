#include "CutestString_internal.h"

char *CuStrVaFormat(const char* format, va_list va){
    size_t n = CuStrLenVaFormat((const char*)CuStrNULL((char*)format), va);//determine number of chars to be printed.
        //Still use snprintf afterwards because only way to detect errors in CuStrLenFormat with debugger

    char *buf = (char*)CuStrAlloc( n );

	vsnprintf(buf, n, format, va);
	return buf;
}

