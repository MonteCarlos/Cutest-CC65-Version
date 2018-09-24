#include <stdheaders.h>
#include <CuTest.h>
#include <CuTest_internal.h>

// ***************************************************************
/** \details
 *
 * \param
 * \param
 * \return
 *
 */
char* CuStringFormatGenerator(char *text1, char *text2, const char *format){
    char *str;
    str = CuStrFormat("%s: \"%s\", %s: \"%s\"", text1, format, text2, format);
    return str;
}
