#include "CuTest_internal.h"

int CuTestFormatReportString(CuString *str, size_t runs, size_t passes, size_t fails, size_t memLeaks){
	//Warning! format string and parameter list must match!!!
	//Only pass size_t or unsigned int!
	CuStringAppendFormat(str,CUTEST_STR_SUMMARY(runs, passes, fails, memLeaks));
	return EXIT_SUCCESS;
}



