#include "CuTest_internal.h"

void CuSuiteSummary(CuSuite* testSuite, FILE* file)
{
	CuTestFprintf(file, CuStringCStr(testSuite->report->reportStr));
}
