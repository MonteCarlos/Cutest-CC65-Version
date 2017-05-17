#include <stdio.h>
#include <assert.h>

#include "CutestString_internal.h"

CuSuite* CuGetSuite(void);
CuSuite* CuStringGetSuite1(void);
CuSuite* CuStringGetSuite2(void);
CuSuite* CuStringGetSuite3(void);

//17,89kB (executable prg), 04.07.2015
//17,74

// TODO (Stefan#1#): cutest-cc65 is still broken: ...
//
//- solve CuStringDelete and CuSuiteDelete problem
//- solve memory allocation problems (sometimes (m)(c)alloc returns NULL)

typedef CuSuitePtr getSuitefnc_t(void);

CuSuite *GetSuite(getSuitefnc_t* getSuitefnc){
    CuSuite* suite = NULL;
    suite = getSuitefnc();
    assert (NULL != suite);
    return suite;
}
CuSize_t testRunner(CuSuite *suite){
	//remember no of total testsuite runs
	static CuSize_t cnt = 0;
	//pre and postfixes of filename of test results
	static char filename_start[] = "testdetails";
	static char filename_end[] = ".txt";
	//allocate array to hold concatenated filename
	char filename[sizeof(filename_start)+sizeof(filename_end)+2];
	FILE *file;

    assert (NULL != suite);

	//Run suite and output results
    printf("*** Testrun: %u ***\n", cnt);
    CuSuiteRun(suite);
    CuSuiteDetails(suite, stdout/*output*/);
	printf("*** End of testrun: %u ***\n\n", cnt);

	//setup filename
    snprintf(filename, sizeof(filename), "%s%2u%s",filename_start,cnt,filename_end);
    //check file io errors
    if (NULL == (file = fopen(filename, "w"))){
		printf("fopen error\n");
    }else{
		CuSuiteDetails(suite, file);
		fclose(file);
    };
	++cnt;
    return CuSuiteGetFailcount(suite);
}

void RunAllTests(void)
{
	//obtain tests of independent functions
	CuSuite* suite = GetSuite(CuStringGetSuite1);//CuSuiteNew();

	//*********************************
	//*** Test CuTestString			***
	//*********************************
		 //assert initialization of suite

    //run tests of independent functions
    printf("*** Running tests of independent functions...\n\n");
	if (testRunner(suite)){
        exit(-1);
	};

	CuSuiteDelete(suite);

	printf("*** Running tests of single dependent functions...\n\n");
	//obtain tests of dependent functions
	suite = GetSuite(CuStringGetSuite2);
    if (testRunner(suite)){
        exit(-1);
	};

    CuSuiteDelete(suite);

	printf("*** Running tests of multiple dependent functions...\n\n");
	//obtain tests of dependent functions
	suite = GetSuite(CuStringGetSuite3);
    if (testRunner(suite)){
        exit(-1);
	};

	CuSuiteDelete(suite);
}


