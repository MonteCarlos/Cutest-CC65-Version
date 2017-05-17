
#include "CutestString_internal.h"

/* Function CuStrFormat returns a new char* array with contents according to the format string and va arguments*/
char *CuStrFormat(const char* format, ...){
    if (format){
		va_list argp;
		char *str;
		va_start(argp, format);
		str = CuStrVaFormat(format, argp);
		va_end(argp);
		return str;
	}
	return NULL;
}
