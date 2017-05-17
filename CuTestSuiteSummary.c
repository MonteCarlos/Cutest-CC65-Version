#include "CuTest_internal.h"

void CuSuiteSummary(CuSuite* testSuite, FILE* file)
{
	if (testSuite){
		CuTestFprintf(file, CuStringCStr(testSuite->report->reportStr));
	}
}
