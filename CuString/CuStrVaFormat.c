#include "CutestString_internal.h"

/** \brief Formats string into newly allocated buffer
 *
 * \param const char* format, va_list va
 * \return char *
 *
 */
char *CuStrVaFormat(const char* format, va_list va){
    //secure that format is not NULL
    if (format){
        va_list va2;
        int n = 0;
        char *buf;

        va_copy(va2, va);
        n = MCLib_getVaFieldwidthFromFormatString(format, va);//determine number of chars to be printed.
            //Still use snprintf afterwards because only way to detect errors in CuStrLenFormat with debugger
        //assert(n > 0);
        buf = CuStrAlloc(n);
        assert(NULL != buf);
        vsnprintf(buf, n+1, format, va2);
        va_end(va2);
        return buf;
    }
    return NULL;
}

