#include <stdheaders.h>
#include "CUnit_CuTest.h"

#define ALLTESTS ATEST(CuStringFormatGenerator_GivenParamsABC_ReturnsACBC)\
    ATEST(CuStringFormatGenerator_GivenParamsABCWithFormatSpec_ReturnsACBCUnexpanded)

#define ATEST(t) void t(void);
ALLTESTS
#undef ATEST

#define ATEST(t) {#t, t},
namedTest_t SuiteCuStringFormatGenerator_testlist[] = {
    ALLTESTS
    {}
};
#undef ATEST

static char *cstring;

int setup_SuiteCuStringFormatGenerator (void) {
    cstring = NULL;
    return 0;
}

int teardown_SuiteCuStringFormatGenerator (void) {
    if (cstring) {
        CuFree (cstring);
    }
    return 0;
}

void CuStringFormatGenerator_GivenParamsABC_ReturnsACBC (void) {
    cstring = CuStringFormatGenerator("a", "b", "c");
    CU_ASSERT_STRING_EQUAL("a: \"c\", b: \"c\"", cstring);
}

void CuStringFormatGenerator_GivenParamsABCWithFormatSpec_ReturnsACBCUnexpanded(void){
    cstring = CuStringFormatGenerator("a", "b", "%d");
    CU_ASSERT_STRING_EQUAL("a: \"%d\", b: \"%d\"", cstring);
}
