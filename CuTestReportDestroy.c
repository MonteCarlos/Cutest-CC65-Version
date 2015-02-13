#include "CuTest_internal.h"

int CuReportDestroy(CuReport_t *report){
    CuStringDelete(report->reportStr);
    return CuFree(report)?EXIT_SUCCESS:EXIT_FAILURE;
}
