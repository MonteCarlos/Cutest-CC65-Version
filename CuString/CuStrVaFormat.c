#include "CutestString_internal.h"

char *CuStrVaFormat(char* format, va_list va){
    char *buf;

	if (format == NULL) {
		format = "NULL";
	}
    va_start(va, format);
	//use (v)snprintf trick to determine number of characters to be printed, beforehand
	buf = (char*)CuStrAlloc( vsnprintf(NULL,0,format,va) );

	vsprintf(buf, format, va);
	return buf;
}

