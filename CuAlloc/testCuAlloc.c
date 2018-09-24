#include "CuAlloc_internal.h"
#include "../CuTest.h"

#include <stdio.h>

void testCuAllocCalculateTotalSize(CuTest_t* tc){
    CuSize_t datasize = 20;
    CuSize_t totalsize = CuAlloc_calculateTotalSize(datasize);
    CuAssertIntEquals(tc, datasize+sizeof(CuAlloc_BufHeader_t), totalsize);
}

void testCuAllocInitHeader(CuTest_t* tc){
    CuAlloc_t allocObj;

    CuSize_t datasize = 20;
    CuSize_t totalsize = datasize+sizeof(CuAlloc_BufHeader_t);
    CuAlloc_initHeader(&allocObj, datasize);

    CuAssertIntEquals(tc, datasize, allocObj.datasize);
    CuAssertIntEquals(tc, totalsize, allocObj.totalsize);
    CuAssertPtrEquals(tc, &allocObj, allocObj.this);
}

void testCuAllocGetDataSize(CuTest_t* tc){
    CuAlloc_t allocObj;

    CuSize_t datasize = 20;

    CuAlloc_initHeader(&allocObj, datasize);

    CuAssertIntEquals(tc, datasize, CuAlloc_getDataSize(&allocObj.array));
}

void testCuAllocGetTotalSize(CuTest_t* tc){
    CuAlloc_t allocObj;

    CuSize_t datasize = 20;
    CuSize_t totalsize = datasize+sizeof(CuAlloc_BufHeader_t);
    CuAlloc_initHeader(&allocObj, datasize);

    CuAssertIntEquals(tc, totalsize, CuAlloc_getTotalSize(&allocObj.array));
}

void testCuAllocGetHeaderAddr(CuTest_t* tc){
    CuAlloc_t allocObj;
    CuAssertPtrEquals(tc, &allocObj, CuAlloc_getHeaderAddr(&allocObj.array));
}

void testCuAllocGetDataAddr(CuTest_t* tc){
    CuAlloc_t allocObj;
    CuAssertPtrEquals(tc, &allocObj.array, CuAlloc_getDataAddr(&allocObj));
}

void testCuAllocGetBufferValidity(CuTest_t* tc){
    CuSize_t datasize = 20;
    CuAlloc_t allocObj;
    CuAlloc_initHeader(&allocObj, datasize);

    CuAssertTrue(tc, CuAlloc_getBufferValidity(&allocObj.array));
    allocObj.dataOffset = 2*offsetof(CuAlloc_t, data);
    CuAssertFalse(tc, CuAlloc_getBufferValidity(&allocObj.array));

}

void testCuFree(CuTest_t* tc){
    int *iVar = CuAlloc(sizeof(int));
    CuSize_t freecount = CuAlloc_getFreeCount();
    CuSize_t alloccount = CuAlloc_getAllocCount();
    bool freeResult = CuFree(iVar);


   // CuAssertTrue(tc, !CuAlloc_getBufferValidity(iVar));
    CuAssertIntEquals(tc, true, freeResult);
    CuAssertIntEquals(tc, alloccount, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, freecount+1, CuAlloc_getFreeCount());

    freeResult = CuFree(iVar);
    //CuAssertTrue(tc, !CuAlloc_getBufferValidity(iVar));
    CuAssertTrue(tc, !freeResult);

}

void testCuCalloc(CuTest_t* tc){
    int intArray[] = {100,200,300,400,500,23};
    unsigned int alloccount = CuAlloc_getAllocCount();
    int *ptr2IntArray = CuCalloc(sizeof(intArray));
    int8_t i;
    //Test, if block is empty
    for ( i = sizeof(intArray)/sizeof(*intArray)-1; i>0; --i){
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
    CuAssertTrue(tc, CuAlloc_getBufferValidity(ptr2IntArray));
    CuAssertIntEquals(tc, alloccount+1, CuAlloc_getAllocCount());

    CuFree(ptr2IntArray);
}

void testCuRealloc(CuTest_t* tc){
    int intArray1[] = {100,200,300,400,500,23};
    int intArray2[] = {1024,512,256,128,64,32,16,8,4,2,1,0};
    int *ptr2IntArray = NULL;
    CuSize_t alloccount = CuAlloc_getAllocCount();
    CuSize_t realloccount = CuAlloc_getReallocCount();
	int8_t i;

    ptr2IntArray = CuRealloc(NULL, sizeof(intArray1));

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
    ptr2IntArray = CuRealloc(ptr2IntArray, sizeof(intArray2));

    //Check correct counting of allocs and reallocs
    CuAssertIntEquals(tc, alloccount, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, realloccount+1, CuAlloc_getReallocCount());

    //Now check content
    for (i = sizeof(intArray1)/sizeof(*intArray1)-1; i>0; --i){
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
    CuAssertTrue(tc,CuAlloc_getBufferValidity(ptr2IntArray));

    CuAssertTrue(tc, CuFree(ptr2IntArray));
}

void testCuAlloc(CuTest_t* tc){
    enum {constTestValInt = 10054};
    unsigned int alloccount = CuAlloc_getAllocCount();

    int *iVar = CuAlloc(sizeof(int));
    CuAssertIntEquals(tc, sizeof(*iVar), CuAlloc_getDataSize(iVar));
    CuAssertIntEquals(tc, sizeof(*iVar)+sizeof(CuAlloc_BufHeader_t), CuAlloc_getTotalSize(iVar));
    CuAssertTrue(tc, CuAlloc_getBufferValidity(iVar));
    CuAssertIntEquals(tc, alloccount+1, CuAlloc_getAllocCount());
    iVar[0] = constTestValInt;
    CuAssertIntEquals(tc, iVar[0], constTestValInt);

    CuFree(iVar);
}

void testAllocCount1(CuTest_t *tc){
    CuAssertIntEquals(tc, 0, CuAlloc_getAllocCount());
    CuAssertIntEquals(tc, 0, CuAlloc_getFreeCount());
    CuAssertIntEquals(tc, 0, CuAlloc_getReallocCount());
}

void testAllocCount2(CuTest_t *tc){
    CuAssertIntEquals(tc, 1, CuAlloc_getPendingFrees());
}

CuSuite_t *CuAlloc_requestEarlyTests(void){
    CuSuite_t* suite = CuSuiteNew();
    assert(NULL != suite);
    SUITE_ADD_TEST(suite, testCuAllocCalculateTotalSize);
    SUITE_ADD_TEST(suite, testCuAllocInitHeader);
    SUITE_ADD_TEST(suite, testCuAllocGetDataSize);
    SUITE_ADD_TEST(suite, testCuAllocGetTotalSize);
    SUITE_ADD_TEST(suite, testCuAllocGetHeaderAddr);
    SUITE_ADD_TEST(suite, testCuAllocGetDataAddr);

    return suite;

}

CuSuite_t *CuAlloc_requestTests(void){
    CuSuite_t* suite = CuSuiteNew();

    assert(NULL != suite);
    //Assert valid memory assignment to suite

    SUITE_ADD_TEST(suite, testCuAllocGetBufferValidity);

	SUITE_ADD_TEST(suite, testCuAlloc);
	SUITE_ADD_TEST(suite, testCuFree);
	SUITE_ADD_TEST(suite, testCuRealloc);
	SUITE_ADD_TEST(suite, testCuCalloc);

	return suite;
}
/*
#ifdef __CC65__ CuSize_t getCuAllocMemSize(void){
	extern uint8_t _BEGIN_LOAD__;
	extern uint8_t _END_LOAD__;
	return &_END_LOAD__-&_BEGIN_LOAD__;
}
#endif
*/
/*
	$4762 (02.07.2015)
	$4747 (using getHeaderAddr and initHeader)
	$40c2 (compiled with -Or)
	$3885 (-or switch also on CuString and CuTest)
	$383f (no register vars)
	$3854 (using getDataAddr)
*/

int main(void){
    int Nofails;

    CuSuite_t* suite = NULL; //
    suite = CuAlloc_requestEarlyTests();
    CuSuiteRun(suite);
    CuSuiteDetails(suite, stdout);
    Nofails = CuSuiteGetFailcount(suite);
    CuSuiteDelete(suite);
    if (Nofails) return Nofails;

    printf("Registering tests...\n");
    printf("Alloc Count before SuiteNew:%u %u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
    suite = CuAlloc_requestTests();
    printf("Alloc Count after request tests:%u %u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());assert(NULL != suite);
    printf("Running tests...\n");
    CuSuiteRun(suite);//This function does not return!
    CuSuiteDetails(suite, stdout);
    printf("Alloc Count after SuiteRun:%u %u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());
 	printf("End testing\n");
 	Nofails = CuSuiteGetFailcount(suite);

	CuSuiteDelete(suite);
	printf("Alloc Count after SuiteDelete:%u %u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount(), CuAlloc_getReallocCount());

	assert (0 == CuAlloc_getPendingFrees());

	assert (0 == CuAlloc_getPendingFrees());
/*
#ifdef __CC65__
	printf("CuAlloc total size: $%x", getCuAllocMemSize());
	#endif // __CC65__
*/
	return Nofails;
}
