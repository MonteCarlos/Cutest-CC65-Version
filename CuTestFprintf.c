#include "CuTest_internal.h"

int CuTestFprintf (FILE *file, char *format, ...) {
    va_list va;
    int outputLength = 0;

    va_start (va, format);

    if (NULL != file) {
        outputLength = vfprintf (file, format, va);
    }

    va_end (va);
    return outputLength;
}
