#include "CuTest_internal.h"

bool CuReportDestroy(CuReport_t *report){
    if (report){
		CuStringDelete(report->reportStr);
		return CuFree(report);
	}
	return EXIT_FAILURE;
}
