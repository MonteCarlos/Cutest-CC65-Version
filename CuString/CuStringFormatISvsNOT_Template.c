#include <stdheaders.h>
#include "../CuTest.h"
#include "../CuTest_internal.h"

// ***************************************************************
/** \details
 *
 * \param
 * \param
 * \return
 *
 */
char* CuStrFormatISvsNOTTemplate(const char *format){
    char *str;
    str = CuStringFormatGenerator("is", "not", format);
    return str;
}

