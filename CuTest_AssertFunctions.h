#ifndef CUTEST_ASSERTFUNCTIONS_H_INCLUDED
#define CUTEST_ASSERTFUNCTIONS_H_INCLUDED

/*
 * Prototypes for CuTest assert functions -- use the convenience macros
 */
void CuFail_Line (CuTest_t *tc, const char *file, unsigned long int line, const char *message2, const char *message);
bool CuAssert_Line (CuTest_t *tc, const char *file, unsigned long int line, const char *message, int condition);
bool CuAssertStrEquals_LineMsg (CuTest_t *tc,
                                const char *file, unsigned long int line, const char *message,
                                const char *expected, const char *actual);
bool CuAssertIntEquals_LineMsg (CuTest_t *tc,
                                const char *file, unsigned long int line, const char *message,
                                int expected, int actual);
/*void CuAssertDblEquals_LineMsg(CuTest* tc,
    const char* file, int line, const char* message,
    double expected, double actual, double delta);*/
bool CuAssertPtrEquals_LineMsg (CuTest_t *tc,
                                const char *file, unsigned long int line, const char *message,
                                const void *expected, const void *actual);
bool CuAssertArrayEquals_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
                                  const void *expected, const void *actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertArrayEqualsStepFunc_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
        bool (*stepfunc) (size_t index, void *expected), const void *actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertArrayElementsConstant_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
        const void *expected, const void *actual, CuSize_t elementsize, CuSize_t len);
bool CuAssertGeneralEquals_LineMsg (CuTest_t *tc, const char *file, unsigned long int line, const char *message,
                                    const void *expected, const void *actual, char *expStr, char *actStr, size_t maxStrLen, CuTestCmpFncPtr_t cmpFnc);


#endif // CUTEST_ASSERTFUNCTIONS_H_INCLUDED
