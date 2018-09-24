#include "CuTest_internal.h"

CuError_t CuSuiteRegisterTests (CuSuite_t *suite, TestfunctionNamePair_t (*testlist) [], CuSize_t n) {
    if (suite) {
        CuTest_t *tc;

        TestfunctionNamePair_t *thistest = (TestfunctionNamePair_t *) testlist;

        for (; n > 0; --n) {
            tc = CuTestNew (thistest->testname, thistest->fnc);

            if (tc) {
                CuSuiteAddTest (suite, tc);
            }
            else {
                fprintf (stderr, "Error registering test %s\n", thistest->testname);
            }

            ++thistest;
        }

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}

CuError_t CuSuiteRegisterNULLTerminatedTestlist (CuSuite_t *suite, void *testlist) {
    assert (suite != NULL);
    assert (testlist != NULL);

    CuTest_t *tc;
    TestfunctionNamePair_t *thistest = &(((TestfunctionNamePair_t *)testlist)[0]);

    while ( thistest->testname != NULL ) {
        assert (thistest->testname != NULL);
        assert (thistest->fnc != NULL);

        tc = CuTestNew (thistest->testname, thistest->fnc);

        if (tc) {
            CuSuiteAddTest (suite, tc);
        }
        else {
            fprintf (stderr, "Error registering test %s\n", thistest->testname);
        }

        ++thistest;
    }

    assert (thistest->testname == NULL);
    assert (thistest->fnc == NULL);
    return EXIT_SUCCESS;
}


