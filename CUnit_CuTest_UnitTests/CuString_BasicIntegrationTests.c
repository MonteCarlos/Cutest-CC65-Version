#include <stdheaders.h>
#include "CUnit_CuTest.h"

#define ALLTESTS ATEST(CuStrVAFormat_GivenNULLPtrAsFormat_ReturnsNULLPtr)\
                 ATEST(CuStrVAFormat_GivenPlainFormatString_ReturnsCopyOfFormatString)\
                 ATEST(CuStrVAFormat_GivenEmptyString_ReturnsNewEmptyString)\
                 ATEST(CuStrVAFormat_GivenIntegerFormatWithPosInteger_ReturnsDecimalStringRepresentation)\
                 ATEST(CuStrVAFormat_GivenIntegerFormatWithNegInteger_ReturnsDecimalStringRepresentationWithMinus)\
                 ATEST(CuStrVAFormat_GivenDblFormatWithPosValue_ReturnsDecimalStringRepresentation)\
                 ATEST(CuStrVAFormat_GivenDblFormatWithNegValue_ReturnsNegDecimalStringRepresentation)


#define ATEST(t) void t(void);
ALLTESTS
#undef ATEST

#define ATEST(t) {#t, t},
namedTest_t SuiteCuStrVAFormatITests_testlist[] = {
    ALLTESTS
    {}
};
#undef ATEST

#define STRINGANDNUM(name, T, num) struct{char *asString; T asNum;} name = {#num, num};

//CuString *teststr;
char *cstring;
const char *format;
char strNum[10];

int setup_SuiteCuStrVAFormatITests (void) {
    cstring = NULL;
    format = NULL;
    memset(strNum, 0, sizeof(strNum));
    return 0;
}

int teardown_SuiteCuStrVAFormatITests (void) {
    if (cstring) {
        CuFree (cstring);
    }
    return 0;
}

char *helper_TestCuStrVaFormat (const char *format, ...) {
    va_list va;
    va_start (va, format);

    return CuStrVaFormat (format, va);
}

// ***************************************************************
// * CuStrVAFormat should just do nothing if NULL ptr for format was given but indicate error by
// * returning NULL itself
// ***************************************************************
void CuStrVAFormat_GivenNULLPtrAsFormat_ReturnsNULLPtr (void) {
    cstring = helper_TestCuStrVaFormat (NULL);

    CU_ASSERT_PTR_NULL(cstring);
    printf("%p", cstring);
}

// ***************************************************************
// * CuStrVAFormat should just copy a format string if it does not
// * contain format specifiers
// ***************************************************************
void CuStrVAFormat_GivenPlainFormatString_ReturnsCopyOfFormatString (void) {
    format = "1234";
    cstring = helper_TestCuStrVaFormat (format);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(format, cstring);
}

// ***************************************************************
// * CuStrVAFormat should create a new empty string if an empty string was given
// ***************************************************************
void CuStrVAFormat_GivenEmptyString_ReturnsNewEmptyString (void) {
    format = "";
    cstring = helper_TestCuStrVaFormat (format);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(format, cstring);
}

// ***************************************************************
// * CuStrVAFormat should format numbers as string for positive numbers
// ***************************************************************
void CuStrVAFormat_GivenIntegerFormatWithPosInteger_ReturnsDecimalStringRepresentation (void) {
    format = "%d";
    STRINGANDNUM(stringNumPair, int, 1234);

    cstring = helper_TestCuStrVaFormat (format, stringNumPair.asNum);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(stringNumPair.asString, cstring);
}

// ***************************************************************
// * CuStrVAFormat should format numbers as string also for negative numbers
// ***************************************************************
void CuStrVAFormat_GivenIntegerFormatWithNegInteger_ReturnsDecimalStringRepresentationWithMinus (void) {
    format = "%d";

    //Keep attention that macro arg does not have space between - and value
    STRINGANDNUM(stringNumPair, int, -1234);

    cstring = helper_TestCuStrVaFormat (format, stringNumPair.asNum);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(stringNumPair.asString, cstring);
}

// ***************************************************************
// * CuStrVAFormat should format numbers as string for positive numbers
// ***************************************************************
void CuStrVAFormat_GivenDblFormatWithPosValue_ReturnsDecimalStringRepresentation (void) {
    format = "%6f";
    STRINGANDNUM(stringNumPair, double, 123.456789);

    cstring = helper_TestCuStrVaFormat (format, stringNumPair.asNum);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(stringNumPair.asString, cstring);
}

// ***************************************************************
// * CuStrVAFormat should format numbers as string also for negative numbers
// ***************************************************************
void CuStrVAFormat_GivenDblFormatWithNegValue_ReturnsNegDecimalStringRepresentation (void) {
    format = "%6f";
    //Keep attention that macro arg does not have space between - and value
    STRINGANDNUM(stringNumPair, double, -123.456789);

    cstring = helper_TestCuStrVaFormat (format, stringNumPair.asNum);

    //Assert that the string is really copied but not just referenced a second time
    CU_ASSERT_NOT_EQUAL(format, cstring);
    CU_ASSERT_STRING_EQUAL(stringNumPair.asString, cstring);
}
