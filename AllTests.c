#include <stdio.h>
#include <assert.h>

#include "CuTest_internal.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();

// TODO (Stefan#1#): cutest-cc65 is still broken: ...
//
//- solve CuStringDelete and CuSuiteDelete problem
//- solve memory allocation problems (sometimes (m)(c)alloc returns NULL)
void RunAllTests(void)
{
	CuString *output = NULL;
	CuSuite* suite = NULL;//CuSuiteNew();

	//*********************************
	//*** Test CuTestString	helpers	***
	//*********************************
	output = CuStringNew();
	suite = CuGetSuite();

	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	CuSuiteDelete(suite);
	CuStringDelete(output);
}


