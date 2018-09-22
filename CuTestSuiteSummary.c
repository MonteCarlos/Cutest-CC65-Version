#include "CuTest_internal.h"

void CuSuiteSummary(CuSuite_t* testSuite, FILE* file)
{
	if (testSuite){
		CuTestFprintf(file, CuStringCStr(testSuite->report->reportStr));
	}
}
