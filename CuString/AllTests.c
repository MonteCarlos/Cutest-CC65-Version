#include <stdio.h>
#include <assert.h>

#include "CutestString_internal.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite1();
CuSuite* CuStringGetSuite2();
CuSuite* CuStringGetSuite3();

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

size_t testRunner(CuSuite *suite){
	static size_t cnt = 0;
	char filename_start[] = "testdetails";
	char filename_end[] = ".txt";

	char filename[sizeof(filename_start)+sizeof(filename_end)+2];
	FILE *file;

    assert (NULL != suite);

    printf("*** Testrun: %d ***\n", cnt);
    CuSuiteRun(suite);
    CuSuiteDetails(suite, stdout/*output*/);
	printf("*** End of testrun: %d ***\n\n", cnt);

    snprintf(filename, sizeof(filename), "%s%2d%s",filename_start,cnt,filename_end);
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


