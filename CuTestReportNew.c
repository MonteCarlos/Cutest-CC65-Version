#include "CuTest_internal.h"

CuReport_t *CuReportNew (void) {
    CuReport_t *tmp = CuCalloc (sizeof (CuReport_t) );
    assert (NULL != tmp);
    tmp->reportStr = CuStringNew();
    return tmp;
}
