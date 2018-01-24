#include <stdheaders.h>
#include "CUnit_CuTest.h"

#define ALLTESTS ATEST(TestCuStringAppendISvsNOT)

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

int setup_SuiteCuStringAppendISvsNOT (void) {
    string = CuStringNew();
    return 0;
}

int teardown_SuiteCuStringAppendISvsNOT (void) {
    CuStringDelete(string);
    return 0;
}

void TestCuStringAppendISvsNOT(void){
    enum {TestISvsNOT_MAXSTRLEN = 100};

    int desired = 100, actual = 103;
    char* leadstr = "Inttest: ";
    CuString *str = CuStringConvertCStr(leadstr);
    char tempstr[TestISvsNOT_MAXSTRLEN];

    CuStringAppendISvsNOT(str, "%d", desired, actual);
    snprintf(tempstr, TestISvsNOT_MAXSTRLEN, "%sis \"%d\" not \"%d\"", leadstr, desired, actual);
    CU_ASSERT_STRING_EQUAL(tempstr, CuStringCStr(str));
}
