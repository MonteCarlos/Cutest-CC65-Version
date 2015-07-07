#include <stdio.h>
#include <assert.h>

#include "CutestString_internal.h"

CuSuite* CuGetSuite();
CuSuite* CuStringGetSuite1();
CuSuite* CuStringGetSuite2();

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
    assert (NULL != suite);
    CuSuiteRun(suite);
    CuSuiteDetails(suite, stdout/*output*/);
    return CuSuiteGetFailcount(suite);
}

void RunAllTests(void)
{
	CuString *output = NULL;
	//obtain tests of independent functions
	CuSuite* suite = GetSuite(CuStringGetSuite1);//CuSuiteNew();

	//*********************************
	//*** Test CuTestString			***
	//*********************************
		 //assert initialization of suite

    //run tests of independent functions
	if (testRunner(suite)){
        exit(-1);
	};

	CuSuiteDelete(suite);

	//obtain tests of dependent functions
	suite = GetSuite(CuStringGetSuite2);
    if (testRunner(suite)){
        exit(-1);
	};

    CuSuiteDelete(suite);

}


