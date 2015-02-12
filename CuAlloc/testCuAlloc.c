#include "CuAlloc_internal.h"
#include "..\CuTest.h"

#include <stdio.h>

void testCuFree(CuTest* tc){
    int *iVar = CuAlloc(sizeof(int));
    bool freeResult = CuFree(iVar);

    CuAssertTrue(tc, !CuAlloc_getBufferValidity(iVar));
    CuAssertIntEquals(tc, true, freeResult);

}

void testCuCalloc(CuTest* tc){
    int intArray[] = {100,200,300,400,500,23};
    int *ptr2IntArray = CuCalloc(sizeof(intArray));

    //Test, if block is empty
    for (int8_t i = sizeof(intArray)/sizeof(*intArray)-1; i>0; --i){
        if (0 != ptr2IntArray[i]){
            CuFail_Msg(tc, "Buf not empty");
            CuTestAppendMessage(tc, " at pos %d",i);
            break;
        }
    }

    //First copy some data to allocated block
    memcpy(ptr2IntArray, intArray, sizeof(intArray));
    //Then check integrity
    CuAssertIntEquals(tc, sizeof(intArray), CuAlloc_getDataSize(ptr2IntArray));
    CuAssertIntEquals(tc, sizeof(intArray)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(ptr2IntArray));
    CuAssertIntEquals(tc, true, CuAlloc_getBufferValidity(ptr2IntArray));

    CuFree(ptr2IntArray);
}

void testCuRealloc(CuTest* tc){
    int intArray1[] = {100,200,300,400,500,23};
    int intArray2[] = {1024,512,256,128,64,32,16,8,4,2,1,0};
    int *ptr2IntArray = NULL;
    unsigned long int alloccount = CuAlloc_getAllocCount();
    unsigned long int realloccount = CuAlloc_getReallocCount();

    CuRealloc(NULL, sizeof(intArray1));
    /*
    //Check correct counting of allocs and reallocs
    CuAssertIntEquals(tc, alloccount+1, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, realloccount, CuAlloc_getReallocCount());
    ++alloccount;

    //Check preconditions
    CuAssertTrue(tc,sizeof(intArray1)!=sizeof(intArray2));
    //First copy some data to allocated block
    memcpy(ptr2IntArray, intArray1, sizeof(intArray1));

    //Then check integrity
    CuAssertIntEquals(tc, sizeof(intArray1), CuAlloc_getDataSize(ptr2IntArray));
    CuAssertIntEquals(tc, sizeof(intArray1)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(ptr2IntArray));
    CuAssertIntEquals(tc, true, CuAlloc_getBufferValidity(ptr2IntArray));

    //Realloc, content should be copied to new block
    /*ptr2IntArray = CuRealloc(ptr2IntArray, sizeof(intArray2));

    //Check correct counting of allocs and reallocs
    CuAssertIntEquals(tc, alloccount, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, realloccount+1, CuAlloc_getReallocCount());

    //Now check content
    for (int8_t i = sizeof(intArray1)/sizeof(*intArray1)-1; i>0; --i){
        if (intArray1[i] != ptr2IntArray[i]){
            CuFail_Msg(tc, "Buf not equals source");
            CuTestAppendMessage(tc, "Pos:%d",i);
            break;
        }
    }

    //Now copy new data with different size
    memcpy(ptr2IntArray, intArray2, sizeof(intArray2));
    //Then check integrity again
    CuAssertIntEquals(tc, sizeof(intArray2), CuAlloc_getDataSize(ptr2IntArray));
    CuAssertIntEquals(tc, sizeof(intArray2)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(ptr2IntArray));
    CuAssertIntEquals(tc, true, CuAlloc_getBufferValidity(ptr2IntArray));
    */
    CuFree(ptr2IntArray);
}

void testCuAlloc(CuTest* tc){
    enum {constTestValInt = 10054};

    int *iVar = CuAlloc(sizeof(int));
    CuAssertIntEquals(tc, sizeof(*iVar), CuAlloc_getDataSize(iVar));
    CuAssertIntEquals(tc, sizeof(*iVar)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(iVar));
    CuAssertIntEquals(tc, true, CuAlloc_getBufferValidity(iVar));
    iVar[0] = constTestValInt;
    CuAssertIntEquals(tc, iVar[0], constTestValInt);

    CuFree(iVar);
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
	SUITE_ADD_TEST(suite, testCuRealloc);
	SUITE_ADD_TEST(suite, testCuCalloc);
    //SUITE_ADD_TEST(suite, testAllocCount2);
	//SUITE_ADD_TEST(suite, test_chartranslation);
	return suite;
}

void main(void){
    //atexit(resetVIC);
    //unsigned long int alloccount;

    CuSuite* suite = NULL; //
    printf("Registering tests...\n");
    printf("Alloc Count before SuiteNew:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
    suite = CuAlloc_requestTests();
    printf("Alloc Count after request tests:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());assert(NULL != suite);
    printf("Running tests...\n");
    CuSuiteRun(suite);//This function does not return!
    CuSuiteDetails(suite, stdout);
    printf("Alloc Count after SuiteRun:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
 	printf("End testing\n");
	CuSuiteDelete(suite);
	printf("Alloc Count after SuiteDelete:%lu %lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());

	assert (0 == CuAlloc_getPendingFrees());
}
