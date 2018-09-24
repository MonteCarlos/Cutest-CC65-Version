#include "CuTest_internal.h"

bool CuTestRun (CuTest_t *tc) {
    if (tc) {
        if (tc->function) {
            (tc->function) (tc);
        }

        if (!tc->assertCnt) {
            fputs ("!no assertions!", stdout);
        }

        tc->ran = 1;

        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
