
//1 Ziffer = 10 Zust
//4 Bits = 16 Zust. -> 10 Zust = 4*10/16 = 2,5 Bits
//1 Byte = 256 Zustände = 8 Bits
//->Int benötigt 8*sizeof(int)/2,5 Zeichen
//2,5 = 5/2 -> 1/2,5 = 2/5
#include "CuTest_internal.h"
bool intCmpFnc(void* exp, void* act, char **expected, char **actual, CuString *msg){
    ///compResult = NULL; //make sure to return NULL pointer if no string is contained. (output functions will deal with that)
                        //as a side effect CuStringAppend will create new CuString
    static char expectedStr[2*8*sizeof(int)/5]; //stringify minimum int value to get max field width incl sign
    static char actualStr[2*8*sizeof(int)/5]; //stringify minimum int value to get max field width incl sign

    snprintf(expectedStr, sizeof(expectedStr)-1, "%d", *((int*)exp));
    snprintf(actualStr, sizeof(actualStr)-1, "%d", *((int*)act));

    *expected = expectedStr;
    *actual = actualStr;

    return (*(int*)exp == *(int*)act);
}

bool CuAssertIntEquals_LineMsg(CuTest* tc, const char* file, unsigned int line, const char* message,
	int expected, int actual)
{
	return CuAssertGeneralEquals_LineMsg(tc, file, line, message, &expected, &actual, intCmpFnc);
	//char* buf = (char*)calloc(STRING_MAX, sizeof(char));
	//assert (NULL != buf);
	/*if (expected != actual){
		//sprintf(buf, "expected <%d> but was <%d>", expected, actual);
		CuFail_Line(tc, file, line, message, " ");
		//CuStringAppend(tc->message, ": ");

		//here axctual and expected are exchanged which is reasoned in the va macros used in more deeply nested function
        CuStringAppendISvsNOT(tc->message, "%d", actual, expected);
		return true;
	}
	//free(buf);
	return false;*/
}
