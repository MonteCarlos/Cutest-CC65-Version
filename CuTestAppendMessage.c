#include "CuTest_internal.h"

int CuTestAppendMessage(CuTest_t *tc, const char* format, ...){
    //CuString *str = CuStringConvertCStr((const char*)tc->message);
    if (tc){
		va_list va;
		va_start(va,format);
		CuStringAppendVariadicFormat(tc->message, format, va);
		va_end(va);
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
