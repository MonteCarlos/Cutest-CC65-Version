#include "CuTest_internal.h"

int CuTestFormatReportString(CuString *str, CuSize_t runs, CuSize_t passes, CuSize_t fails, CuSize_t memLeaks){
	//Warning! format string and parameter list must match!!!
	//Only pass CuSize_t or unsigned int!
	CuStringAppendFormat(str,CUTEST_STR_SUMMARY(runs, passes, fails, memLeaks));
	return EXIT_SUCCESS;
}



