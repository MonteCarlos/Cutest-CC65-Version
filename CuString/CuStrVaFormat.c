#include "CutestString_internal.h"

char *CuStrVaFormat(const char* format, va_list va){
	//Do not use CuStrNULL because parameter list implies certain control seqs
    CuSize_t n = MCLib_getVaFieldwidthFromFormatString(format, va);//determine number of chars to be printed.
        //Still use snprintf afterwards because only way to detect errors in CuStrLenFormat with debugger

    char *buf = (char*)CuStrAlloc(n);

	vsnprintf(buf, n, format, va);
	return buf;
}

