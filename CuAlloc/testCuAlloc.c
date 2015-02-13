#include "CuAlloc_internal.h"
#include "..\CuTest.h"

#include <stdio.h>

void testCuFree(CuTest* tc){
    int *iVar = CuAlloc(sizeof(int));
    bool freeResult = CuFree(iVar);

    CuAssertTrue(tc, !CuAlloc_getBufferValidity(iVar));
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

void testAllocCount1(CuTest *tc){
    CuAssertIntEquals(tc, 0, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, 0, CuAlloc_getFreeCount());
    CuAssertIntEquals(tc, 0, CuAlloc_getReallocCount());
}

void testAllocCount2(CuTest *tc){
    CuAssertIntEquals(tc, 1, CuAlloc_getPendingFrees());
}

CuSuite *CuAlloc_requestTests(void){
    CuSuite* suite = CuSuiteNew();

    assert(NULL != suite);
    //Assert valid memory assignment to suite


	//SUITE_ADD_TEST(suite, test_stripescroll_alloc);
	//SUITE_ADD_TEST(suite, testAllocCount1);
	SUITE_ADD_TEST(suite, testCuAlloc);
	SUITE_ADD_TEST(suite, testCuFree);
    //SUITE_ADD_TEST(suite, testAllocCount2);
	//SUITE_ADD_TEST(suite, test_chartranslation);
	return suite;
}

int main(void){
    //atexit(resetVIC);
    //unsigned long int alloccount;

    CuSuite* suite = NULL; //
    printf("Registering tests...\n");
    printf("Alloc Count before SuiteNew:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
    suite = CuAlloc_requestTests();
    printf("Alloc Count after request tests:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());assert(NULL != suite);
    printf("Running tests...\n");
    //CuSuiteRun(suite);//This function does not return!
    printf("Alloc Count after SuiteRun:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
 	printf("End testing\n");
	CuSuiteDelete(suite);
	printf("Alloc Count after SuiteDelete:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());

	assert (0 == CuAlloc_getPendingFrees());
	return EXIT_SUCCESS;
}
