#include <stdio.h>
#include <assert.h>

#include "CuTest_internal.h"
#include <signal.h>

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();

static void illSignalHandler(int sig){
	printf("!!! Exception occured in RunAllTests. Signal %d !!!\n\n", sig);
	signal(SIGSEGV, SIG_IGN);
}


// TODO (Stefan#1#): cutest-cc65 is still broken: ...
//
//- solve CuStringDelete and CuSuiteDelete problem
//- solve memory allocation problems (sometimes (m)(c)alloc returns NULL)
int RunAllTests(CuSuite* suite, FILE* file)
{
    int NoFails = 1;
	//__sighandler_t prevHandler = signal(SIGSEGV, illSignalHandler);

	//*********************************
	//*** Test CuTestString	helpers	***
	//*********************************
	//printf("Alloc Count before getSuite:%lu %lu\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	//suite = CuGetSuite();
    printf("Alloc Count at start of RunAllTests:%u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	printf("Alloc Count after SuiteRun:%u\n", CuAlloc_getAllocCount());
	//CuSuiteSummary(suite, output);

	CuSuiteDetails(suite, file);

	/*file = fopen("CuTest.log","w");
	if (NULL != file){
        CuSuiteDetails(suite, file);
	}
	fclose(file);*/
	//printf("%s\n", output->buffer);
	printf("Alloc Count before SuiteDelete:%u\n", CuAlloc_getAllocCount());
	NoFails = CuSuiteGetFailcount(suite);
	CuSuiteDelete(suite);
	printf("Alloc Count after SuiteDelete:%u %u\n", CuAlloc_getAllocCount(), CuAlloc_getFreeCount());
	//signal(SIGSEGV, prevHandler);

    return NoFails;
}


