#include "CuTest_internal.h"

void CuSuiteSummary(CuSuite* testSuite, FILE* file)
{
	CuString *str = CuReportGenerateMessage(testSuite);
	CuTestFprintf(file, CuStringCStr(str));
}
