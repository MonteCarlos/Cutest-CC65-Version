#include <stdio.h>
#include <assert.h>

#include "CuTest_internal.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();

// TODO (Stefan#1#): cutest-cc65 is still broken: ...
//
//- solve CuStringDelete and CuSuiteDelete problem
//- solve memory allocation problems (sometimes (m)(c)alloc returns NULL)
int RunAllTests(void)
{
	CuSuite* suite = NULL;//CuSuiteNew();
    FILE *file;
    int NoFails = 1;

	//*********************************
	//*** Test CuTestString	helpers	***
	//*********************************
	printf("Alloc Count before getSuite:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	suite = CuGetSuite();
    printf("Alloc Count after getSuite:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	printf("Alloc Count after SuiteRun:%lu\n", CuAlloc_getAllocCount());
	//CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, stdout);
	/*file = fopen("CuTest.log","w");
	if (NULL != file){
        CuSuiteDetails(suite, file);
	}
	fclose(file);*/
	//printf("%s\n", output->buffer);
	printf("Alloc Count before SuiteDelete:%lu\n", CuAlloc_getAllocCount());
	NoFails = CuSuiteGetFailcount(suite);
	CuSuiteDelete(suite);
	printf("Alloc Count after SuiteDelete:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
    return NoFails;
}


