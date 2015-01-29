#include "CuAlloc_internal.h"
#include "..\CuTest.h"

#include <stdio.h>

void testCuFree(CuTest* tc){
    int *iVar = CuAlloc(sizeof(int));
    bool freeResult;
    CuAssertIntEquals(tc, false, CuAlloc_getBufferValidity(iVar));
    freeResult = CuFree(iVar);
    CuAssertIntEquals(tc, true, freeResult);

}

void testCuAlloc(CuTest* tc){
    enum {constTestValInt = 10054};

    int *iVar = CuAlloc(sizeof(int));
    CuAssertIntEquals(tc, sizeof(*iVar), CuAlloc_getDataSize(iVar));
    CuAssertIntEquals(tc, sizeof(*iVar)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(iVar));
    CuAssertIntEquals(tc, true, CuAlloc_getBufferValidity(iVar));
    iVar[0] = constTestValInt;
    CuAssertIntEquals(tc, iVar[0], constTestValInt);

    free(iVar);
}

CuSuite *CuAlloc_requestTests(void){
    CuSuite* suite = CuSuiteNew();
    assert(NULL != suite);
    //Assert valid memory assignment to suite

	//SUITE_ADD_TEST(suite, test_stripescroll_alloc);
	SUITE_ADD_TEST(suite, testCuAlloc);
	SUITE_ADD_TEST(suite, testCuFree);
	//SUITE_ADD_TEST(suite, test_chartranslation);
	return suite;
}

void main(void){
    //atexit(resetVIC);

    CuSuite* suite = NULL; //
    suite = CuAlloc_requestTests();

    assert(NULL != suite);
    CuSuiteRun(suite);//This function does not return!
 	CuSuiteDetails(suite, stdout);

	CuSuiteDelete(suite);
}
