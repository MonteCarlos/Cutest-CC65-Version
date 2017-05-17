#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief Converts c_str(char *) to CuString
 *
 * \param const char* text
 * \return CuString* string with content of c_str
 *
 */
CuString* CuStringConvertCStr(const char* text){
    CuString *str = CuStringNew();
    CuStringAppend(str, text);//NULL is handled by Append
    return str;
}
