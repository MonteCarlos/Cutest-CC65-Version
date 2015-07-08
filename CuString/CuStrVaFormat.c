#include "CutestString_internal.h"

char *CuStrVaFormat(const char* format, va_list va){
    char *buf;

	format = (const char*)CuStrNULL((char*)format);

	//use (v)snprintf trick to determine number of characters to be printed, beforehand
	buf = (char*)CuStrAlloc( vsnprintf(NULL,0,format,va) );

	vsprintf(buf, format, va);
	return buf;
}

