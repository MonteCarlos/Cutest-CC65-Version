#include <stdheaders.h>
#include "CUnit_CuTest.h"

#define ALLTESTS ATEST(foo) ATEST(bar)

#define ATEST(t) void t(void);
    ALLTESTS
#undef ATEST

#define ATEST(t) {#t, t},
namedTest_t suite1_testlist[] = {
    ALLTESTS
    {}
};
#undef ATEST
int setup_suite1( void ) {return 0;}
int teardown_suite1( void ) {return 0;}


void foo( void ) {
    CU_FAIL( "foo failed!" );
}

void bar( void ) {
    CU_FAIL( "bar failed!" );
}
