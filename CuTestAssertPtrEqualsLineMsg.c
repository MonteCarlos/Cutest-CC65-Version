#include "CuTest_internal.h"

//#pragma warn(unused-param, push, off)
bool ptrCmpFnc (const void *exp, const void *act, char *expectedStr, char *actualStr, size_t maxStrLen, CuString *msg) {
    (void)msg; //just to omit unused param warning

    //write ptrs into passed string buffers
    snprintf ( (char *) expectedStr, maxStrLen, "%p", exp);
    snprintf ( (char *) actualStr, maxStrLen, "%p", act);

    return (void *) exp == (void *) act;
}

bool CuAssertPtrEquals_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
                                const void *expected, const void *actual) {
    char expectedStr[sizeof (uintptr_t) * 2 + 2 + 1]; //reserve minimum field width capable of holding smallest int. each byte needs
    //two hex digits with additional 0x and \0
    char actualStr[sizeof (uintptr_t) * 2 + 2 + 1];

    return CuAssertGeneralEquals_LineMsg (tc, file, line, message, expected, actual, expectedStr, actualStr,
                                          sizeof (expectedStr), ptrCmpFnc);

    return true;
}
