#include "CuTestTest.h"

/*-------------------------------------------------------------------------*
 * Helper functions
 *-------------------------------------------------------------------------*/

static int equals_zero = 0;//prevents error message about condition beeing always true
static int equals_one = 1;

void TestPasses(CuTest* tc)
{
	CuAssert(tc, "test should pass", equals_one == equals_zero + equals_one);
}

void zTestFails(CuTest* tc)
{
	CuAssert(tc, "test should fail", equals_one == equals_one + equals_one);
}
