#include "CuTest_internal.h"

bool CuReportDestroy(CuReport_t *report){
    CuStringDelete(report->reportStr);
    return CuFree(report);
}
