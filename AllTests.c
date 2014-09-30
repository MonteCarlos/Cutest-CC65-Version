#include <stdio.h>
#include <assert.h>

#include "CuTest.h"

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


	//CuSuiteAddSuite(suite, CuStringGetSuite());
	/*suite = CuStringGetSuite();
	output = CuStringNew();
	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	CuSuiteDelete(suite);
	CuStringDelete(output);*/

	output = CuStringNew();
	suite = CuGetSuite();
	//CuSuiteAddSuite(suite, CuGetSuite());

	assert (NULL != suite); //assert initialization of suite
	CuSuiteRun(suite);//This function does not return!

CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
	CuSuiteDelete(suite);
}

int main(void)
{
	printf("CuTest V1.5 running...\n");

	RunAllTests();
	return 0;
}
