#include "CuTest.h"

CuError_t CuSuiteInitRunReport (CuSuiteInitFnc_t *initSuite, FILE *file, void *params) {
    CUSUITE_OPEN (suite);

    if (initSuite (suite, params) >= 0 ) {
        CuSuiteRun (suite);
        CuSuiteDetails (suite, file);
        CUSUITE_CLOSE (suite);
        return 0;
    }
    else {
        fprintf (stderr, "Error initializing suite %p\n", suite);
        CUSUITE_CLOSE (suite);
        return -1;
    }
}

