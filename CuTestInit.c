#include "CuTest_internal.h"

void CuTestInit (register CuTest_t *t, const char *name, TestFunction function) {
    if (t) {
        t->name = CuStringConvertCStr (name); //CuStrCopy(name);
        t->failed = t->ran = t-> reported = t->memoryleak = 0;
        t->message = CuStringNew();
        t->function = function;
        t->setup = t->teardown = NULL;
        t->assertCnt = 0;
    }
}
