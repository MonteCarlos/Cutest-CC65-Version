#include "CutestString_internal.h"

/** \brief Formats string into newly allocated buffer
 *
 * \param const char* format, va_list va
 * \return char *
 *
 */
char *CuStrVaFormat(const char* format, va_list va){
    va_list va2;
    int n = 0;
    char *buf;

    va_copy(va2, va);
	//Do not use CuStrNULL because parameter list implies certain control seqs

	n = MCLib_getVaFieldwidthFromFormatString(format, va);//determine number of chars to be printed.
        //Still use snprintf afterwards because only way to detect errors in CuStrLenFormat with debugger
	//assert(n > 0);
    buf = CuStrAlloc(n);
	assert(NULL != buf);
	vsnprintf(buf, n, format, va2);
	return buf;
}

