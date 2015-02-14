#include "CuTest_internal.h"

CuString *CuTestGenerateReportString(CuSuite *suite){
	CuString *str = CuStringNew();
	size_t count = suite->count, fails = suite->failCount;
	CuStringAppendFormat(str,"Runs:%u, Passes:%u, Fails:%u\n", count, count-fails, fails);
	return str;
}



