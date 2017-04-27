
#include "CuTest_internal.h"

int CuRegisterTests(CuSuite *suite, TestfunctionNamePair_t (*testlist)[], size_t n){
	size_t i;
	TestfunctionNamePair_t *thistest = (TestfunctionNamePair_t*)testlist;

	for (i=0; i<n; ++i){
		CuSuiteAdd(suite, CuTestNew(thistest->testname, thistest->fnc));
		++thistest;
	}
	return EXIT_SUCCESS;
}

