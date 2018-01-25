#include <stdheaders.h>
#include "CUnit_CuTest.h"

#define ALLTESTS ATEST(CuStringAppendISvsNOT_PassedEmptyCuStrAndTwoInts_ReturnsIsActualNotDesired)

#define ATEST(t) void t(void);
ALLTESTS
#undef ATEST

#define ATEST(t) {#t, t},
namedTest_t SuiteCuStringAppendISvsNOT_testlist[] = {
    ALLTESTS
    {}
};
#undef ATEST

static CuString *string;
char tempstr[100];

int setup_SuiteCuStringAppendISvsNOT (void) {
    string = CuStringNew();
    memset(tempstr, 0, sizeof(tempstr));
    return 0;
}

int teardown_SuiteCuStringAppendISvsNOT (void) {
    CuStringDelete(string);
    return 0;
}

void CuStringAppendISvsNOT_PassedEmptyCuStrAndTwoInts_ReturnsIsActualNotDesired(void){
    int desired = 100, actual = 103;
    char *strTemplate;

    CuStringAppendISvsNOT(string, "%d", desired, actual);
    strTemplate = CuStrFormatISvsNOTTemplate("%d");
    snprintf(tempstr, sizeof(tempstr), strTemplate, desired, actual);
    CU_ASSERT_STRING_EQUAL(tempstr, CuStringCStr(string));
    CuFree(strTemplate);
}

void TestCuStringAppendISvsNOT2(void){
    enum {TestISvsNOT_MAXSTRLEN = 100};

    int desired = 100, actual = 103;
    char* leadstr = "Inttest: ";
    CuString *str = CuStringConvertCStr(leadstr);
    char tempstr[TestISvsNOT_MAXSTRLEN];

    CuStringAppendISvsNOT(str, "%d", desired, actual);
    snprintf(tempstr, TestISvsNOT_MAXSTRLEN, "%sis \"%d\" not \"%d\"", leadstr, desired, actual);
    CU_ASSERT_STRING_EQUAL(tempstr, CuStringCStr(str));
}
