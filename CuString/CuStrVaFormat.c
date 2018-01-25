#include "CutestString_internal.h"

/** \brief Formats string into newly allocated buffer
 *
 * \param const char* format, va_list va
 * \return char *
 *
 */
char *CuStrVaFormat (const char *format, va_list va) {
    //secure that format is not NULL
    if (format) {
        va_list va2;
        int n = 0;
        char *buf = NULL;

        //make copy of original va_list
        va_copy (va2, va);
        n = MCLib_getVaFieldwidthFromFormatString (format, va); //determine number of chars to be printed.

        //error getting fieldwidth?
        if (n >= 0) {
            buf = CuStrAlloc (n);
            //buf was allocated correctly?
            if (buf) {
                //use copy of va_list, here because it was already used in
                //MCLib_getVaFieldwidthFromFormatString
                vsnprintf (buf, n + 1, format, va2);
            }
            va_end (va2);
            return buf;
        }

        return NULL;
    }
    return CuStrNULL(NULL);
}

