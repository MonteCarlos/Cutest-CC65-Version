#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int savePrintf(char *format, ...){
    char buf;
    int result;
    va_list va;
    va_list va2;
    va_start(va, format);
    va_copy(va2, va);
    result = vsnprintf(&buf, 1, format, va);
    if (result < 0){
        fprintf(stderr, "Error printing %s\n", format);
    }else{
        vfprintf(stdout, format, va2);
    }
    va_end(va2);
    va_end(va);
    return result;
}

int main()
{
    int result = savePrintf("Hello world !%#\n", 10000000);
    savePrintf("Printed %d characters\n", result);
    return 0;
}
