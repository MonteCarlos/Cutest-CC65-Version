#include "CuTest_internal.h"

void CuSuiteDelete(CuSuite *testSuite)
{
        unsigned int n;
        assert (NULL != testSuite);
        for (n=0; n < MAX_TEST_CASES; n++)
        {
			//printf("%d\n",n);
                if (testSuite->list[n])
                {
                        CuTestDelete(testSuite->list[n]);
                        //assert (NULL != testSuite->list);
                        //free(testSuite->list);
                }
        }

        free(testSuite);
}
