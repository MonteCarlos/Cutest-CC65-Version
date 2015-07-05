#include <stdio.h>
#include <assert.h>

#include "CutestString_internal.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite();

//17,89kB (executable prg), 04.07.2015
//17,74

// TODO (Stefan#1#): cutest-cc65 is still broken: ...
//
//- solve CuStringDelete and CuSuiteDelete problem
//- solve memory allocation problems (sometimes (m)(c)alloc returns NULL)
void RunAllTests(void)
{
	CuString *output = NULL;
	CuSuite* suite = NULL;//CuSuiteNew();

	//*********************************
	//*** Test CuTestString			***
	//*********************************
	suite = CuStringGetSuite();
	//output = CuStringNew();

	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	//CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, stdout/*output*/);
	//printf("%s\n", output->buffer);
	CuSuiteDelete(suite);
	//CuStringDelete(output);//*/

	//*********************************
	//*** Test CuTestString	helpers	***
	//*********************************
	//output = CuStringNew();
	suite = CuGetSuite();

	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	//CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, stdout/*output*/);
	//printf("%s\n", output->buffer);
	CuSuiteDelete(suite);
	//CuStringDelete(output);
}


