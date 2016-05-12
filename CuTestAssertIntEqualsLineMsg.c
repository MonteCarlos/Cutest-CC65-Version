
//8Bit: 3 Dez Zeichen
//16Bit: 5 Dez Zeichen
//24Bit: 8 Dez Zeichen
//32Bit: 10 Dez Zeichen
//64Bit:
//1 Ziffer = 10 Zust
//4 Bits = 16 Zust. -> 10 Zust = 4*10/16 = 2,5 Bits
//1 Byte = 256 Zustände = 8 Bits
//->Int benötigt 8*sizeof(int)/2,5 Zeichen
//2,5 = 5/2 -> 1/2,5 = 2/5
#include "CuTest_internal.h"
bool intCmpFnc(const void* exp, const void* act, char *expectedStr, char *actualStr, size_t maxChars, CuString *str){
    str; //just to omit unused param warning

    //write ints into passed string buffers
    snprintf(expectedStr, maxChars, "%d", *((int*)exp));
    snprintf(actualStr, maxChars, "%d", *((int*)act));

    return (*(int*)exp == *(int*)act);
}

bool CuAssertIntEquals_LineMsg(CuTest* tc, const char* file, unsigned int line, const char* message,
	int expected, int actual)
{
	minWidthIntCharArray_t expectedStr; //reserve minimum field width capable of holding smallest int
    minWidthIntCharArray_t actualStr;

	return CuAssertGeneralEquals_LineMsg(tc, file, line, message, &expected, &actual,
                                      expectedStr, actualStr, sizeof(expectedStr), intCmpFnc);
}
