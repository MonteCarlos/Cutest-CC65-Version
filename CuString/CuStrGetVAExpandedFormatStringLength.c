//#include <stdheaders.h>
#include "CuString/CutestString_internal.h"

int CuStrGetVAExpandedFormatStringLength(const char *format, va_list va){
	//just wrap library function for whatever this may be useful
	return MCLib_getVaFieldwidthFromFormatString(format, va);
}

