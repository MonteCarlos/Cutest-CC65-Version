/*
 *  Simple example of a CUnit unit test.
 *
 *  This program (crudely) demonstrates a very simple "black box"
 *  test of the standard library functions fprintf() and fread().
 *  It uses suite initialization and cleanup functions to open
 *  and close a common temporary file used by the test functions.
 *  The test functions then write to and read from the temporary
 *  file in the course of testing the library functions.
 *
 *  The 2 test functions are added to a single CUnit suite, and
 *  then run using the CUnit Basic interface.  The output of the
 *  program (on CUnit version 2.0-2) is:
 *
 *           CUnit : A Unit testing framework for C.
 *           http://cunit.sourceforge.net/
 *
 *       Suite: Suite_1
 *         Test: test of fprintf() ... passed
 *         Test: test of fread() ... passed
 *
 *       --Run Summary: Type      Total     Ran  Passed  Failed
 *                      suites        1       1     n/a       0
 *                      tests         2       2       2       0
 *                      asserts       5       5       5       0
 */

#include <stdio.h>
#include <string.h>
//#include <CUnit/Console.h>
#include <CuTest_internal.h>

#include "CUnit_CuTest.h"

typedef struct {
    const char *name;
    CU_InitializeFunc setup;
    CU_CleanupFunc teardown;
    namedTest_t *testlist;
} addSuiteArg_t;

CU_ErrorCode addTestsToSuite( CU_pSuite pSuite, namedTest_t *testlist ) {
    uint8_t i;
    namedTest_t *testfunc;

    for( i = 0; i < 100; ++i ) {
        testfunc = &testlist[i];

        if( !testfunc->name ) { break; }

        if( NULL == CU_add_test( pSuite, testfunc->name, testfunc->test ) ) {
            return CU_get_error();
        }
    }

    if( 100 == i ) {
        printf( "Too many tests per Suite in %s", pSuite->pName );
        CU_ASSERT_TRUE_FATAL( false );
    }

    return 0;
}

CU_ErrorCode addSuites( void ) {

#define XSUITE(suite) {#suite, setup_##suite, teardown_##suite, suite##_testlist},
    addSuiteArg_t suites[] = {
        ALLSUITES
        {0}
    };
#undef XSUITE

    CU_pSuite pSuite = NULL;

    uint8_t i;
    CU_ErrorCode error;

    for( i = 0; i < SUITECOUNT; ++i ) {
        pSuite = CU_add_suite( suites[i].name, suites[i].setup, suites[i].teardown );

        if( NULL == pSuite ) {
            CU_cleanup_registry();
            return CU_get_error();
        }

        error = addTestsToSuite( pSuite, suites[i].testlist );

        if( CUE_SUCCESS != error ) {
            return error;
        }
    }

    return CUE_SUCCESS;
}

/* The main() function for setting up and running the tests.
 * Returns a CUE_SUCCESS on successful running, another
 * CUnit error code on failure.
 */
int main() {
    CU_ErrorCode errCode;

    /* initialize the CUnit test registry */
    if( CUE_SUCCESS != CU_initialize_registry() ) {
        puts( "Registry initialization error!" );
        return CU_get_error();
    }

    /* add the tests to the suite */
    /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
    errCode = addSuites();

    if( CUE_SUCCESS != errCode ) {
        puts( "Error adding suites!" );
        return CU_get_error();
    }

    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode( CU_BRM_VERBOSE );
    CU_basic_run_tests();
    //CU_curses_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
