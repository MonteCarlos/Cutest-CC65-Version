#include "CuTest_internal.h"

bool strCmpFnc(const void* exp, const void* act, char *expectedStr, char *actualStr, size_t maxChars, CuString *str){
    (void)str; //just to omit unused param warning
    (void)expectedStr;
    (void)actualStr;
    (void)maxChars;

    if (exp) { //check, if exp is valid ptr
        if (act) { //check, if act is valid ptr
            return  strcmp (exp, act) == 0; //compare string if both ptr are valid
        }

        return false; //act is NULL ptr
    }

    //exp is NULL ptr, so return if act is NULL, too
    return NULL == act;
}

bool CuAssertStrEquals_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
                                const char *expected, const char *actual) {
    //for string comparison we need no string conversion as expected and actual are strings already
    return CuAssertGeneralEquals_LineMsg (tc, file, line, message, expected, actual,
                                          (char *) expected, (char *) actual, sizeof (expected), strCmpFnc);
}
