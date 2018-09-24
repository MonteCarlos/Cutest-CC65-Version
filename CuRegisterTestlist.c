#include "CuTest_internal.h"

CuError_t CuSuiteRegisterTestlist (CuSuite_t *suite, CuTestlist_t *testlist) {
    CuTest_t *tc;
    CuSize_t i;

    assert ( NULL != suite);
    // We can savely assert here, as a call with suite == NULL makes no sense at all and it
    // makes no sense to branch on NULL ptr for the same reason.

    assert ( NULL != testlist);
    assert ( NULL != testlist->tests);
    // The same applies to testlist argument and the tests array. We want to register tests and the tests to register are
    // passed in the testlist structure by ref. How can we register tests if testlist is NULL??? See.


    TestfunctionNamePair_t *thistest = (TestfunctionNamePair_t *) testlist->tests;
    assert ( NULL != thistest);


    for ( i = testlist->elemCnt; i > 0; --i) {
        assert ( NULL != thistest->testname);
        assert ( strlen (thistest->testname) > 0);
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
