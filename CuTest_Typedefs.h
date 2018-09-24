#ifndef CUTEST_TYPEDEFS_H_INCLUDED
#define CUTEST_TYPEDEFS_H_INCLUDED

#include "CuString/CutestString.h"

/*
 * ---------------------------------
 * Typedefs for CuTest related types
 * ---------------------------------
 */

/**< Dummy definition for CuSuite to hide internal details of CuSuite struct */
typedef struct CuSuite_tag CuSuite_t;
/**< Dummy definition for CuTest to hide internal details of CuTest struct */
typedef struct CuTest_tag CuTest_t;
/**< Dummy definition for CuReport to hide internal details of CuReport struct */
typedef struct CuReport_tag CuReport_t;

/**< Typedef pointer to CuSuite and CuTest to avoid intense use of * */
typedef CuSuite_t *CuSuitePtr_t;
typedef CuTest_t *CuTestPtr_t;

/*
 * ---------------------------------
 * Typedefs callback functions
 * ---------------------------------
 */

/**< Typedef for function to be called before each test of a suite */
typedef int CuTest_SetupFnc_t (void *args);
/**< Typedef for function to be called after each test of a suite */
typedef int CuTest_TeardownFnc_t (void *args);
typedef CuError_t CuSuiteInitFnc_t (CuSuite_t *suite, void *args);

/**< Typedef for a function which is considered as a unit test*/
typedef void (*TestFunction) (CuTest_t *);
/**< typedef of a pair of a testname string and a pointer to a test function*/
typedef struct TestfunctionNamePair_tag {
    char *testname;
    TestFunction fnc;
} TestfunctionNamePair_t;

typedef struct CuTestlist_tag{
    CuSize_t elemCnt;
    TestfunctionNamePair_t tests[];
}CuTestlist_t;

/**< Typedef for a compare function used in CuAssert[...]Equals */
typedef bool CuTestCmpFnc_t (const void *a, const void *b, char *exp,
                             char *act, size_t maxStrLen, CuString *message);

/**< Convenience typedef: Pointer to compare function */
typedef CuTestCmpFnc_t *CuTestCmpFncPtr_t;

#endif // CUTEST_TYPEDEFS_H_INCLUDED
