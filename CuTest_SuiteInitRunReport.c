#include "CuTest.h"

CuError_t CuTest_SuiteInitRunReport(CuError_t (*initSuite)(CuSuite_t *suite), FILE *file){
    CUSUITE_OPEN(suite);
    initSuite(suite);

    CuSuiteRun(suite);
    CuSuiteDetails(suite, file);
    CUSUITE_CLOSE(suite);
    return 0;
}

