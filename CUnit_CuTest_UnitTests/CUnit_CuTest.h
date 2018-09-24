#ifndef CUNIT_CUTEST_H_INCLUDED
#define CUNIT_CUTEST_H_INCLUDED

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../CuTest.h"
#include "../CuTest_internal.h"

//typedef int AddTestsFunction_t(CU_pSuite suite);

typedef struct {
    const char *name;
    CU_TestFunc test;
} namedTest_t;

#define ALLSUITES XSUITE(SuiteCuStrVAFormatITests)\
                  XSUITE(SuiteCuStringFormatGenerator)\
                  XSUITE(SuiteCuStringAppendISvsNOT)

#define XSUITE(suite) suite,
    enum SUITEIDS {ALLSUITES SUITECOUNT};
#undef XSUITE

#define XSUITE(suite) extern namedTest_t suite##_testlist[];
    ALLSUITES
#undef XSUITE

#define XSUITE(suite) int setup_##suite(void);
    ALLSUITES
#undef XSUITE

#define XSUITE(suite) int teardown_##suite(void);
    ALLSUITES
#undef XSUITE

#endif // CUNIT_CUTEST_H_INCLUDED
