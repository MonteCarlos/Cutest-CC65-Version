#include "CutestString_internal.h"

/** \brief Formats string into newly allocated buffer
 *
 * \param const char* format, va_list va
 * \return char *
 *
 */
char *CuStrVaFormat(const char* format, va_list va){
	//Do not use CuStrNULL because parameter list implies certain control seqs
    int n;
        //Still use snprintf afterwards because only way to detect errors in CuStrLenFormat with debugger
	char *buf = NULL;
	va_list va2;
	va_copy(va2, va);
	n = MCLib_getVaFieldwidthFromFormatString(format, va);//determine number of chars to be printed.

	assert(n > 0);
    buf = CuStrAlloc(n);
	assert(NULL != buf);
	//va_start(va, format);
	vsnprintf(buf, n+1, format, va2);
	//va_end(va);
	return buf;
}

