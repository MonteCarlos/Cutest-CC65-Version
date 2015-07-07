#include "CutestString_internal.h"

char *CuStrVaFormat(const char* format, va_list va){
    char *buf;

	if (format == NULL) {
		format = "NULL";
	}

	//use (v)snprintf trick to determine number of characters to be printed, beforehand
	buf = (char*)CuStrAlloc( vsnprintf(NULL,0,format,va) +1 );

	vsprintf(buf, format, va);
	return buf;
}

