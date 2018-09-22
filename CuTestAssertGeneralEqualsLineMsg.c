
#include "CuTest_internal.h"

bool CuAssertGeneralEquals_LineMsg(CuTest_t* tc, const char* file, unsigned long int line, const char* message,
	const void *expected, const void *actual, char *expectedStr, char *actualStr, size_t maxStrLen, CuTestCmpFncPtr_t cmpFnc)
{
	if (tc){
		bool result;

		//increase counter for assertions within that test
		++tc->assertCnt;

		//char *expectedStr=NULL, *actualStr=NULL; //init to NULL to enable tracking of missing ptr assignment
	   // CuString *cmpmsg = CuStringNew();
		//char* buf = (char*)calloc(STRING_MAX, sizeof(char));
		//assert (NULL != buf);
		//String functions will create new instance if NULL Ptr is passed
		//CuString *compResult = CuStringNew();
		if ( false == (result=cmpFnc(expected,actual,expectedStr, actualStr, maxStrLen, tc->message/*cmpmsg*/)) ){
			assert(NULL != expectedStr);
			assert(NULL != actualStr);

			//sprintf(buf, "expected <%d> but was <%d>", expected, actual);
			CuFail_Line(tc, file, line, message, " ");
			//CuStringAppend(tc->message, ": ");

			//here axctual and expected are exchanged which is reasoned in the va macros used in more deeply nested function
			//CuStringAppendISvsNOT(tc->message, "%d", actual, expected);
			CuStringAppendISvsNOT(tc->message, "%s", actualStr, expectedStr);
		   // CuTestAppendMessage(tc, CuStringCStr(cmpmsg));
			//return true;
		}
		//CuStringDelete(compResult);
		//free(buf);
		//CuStringDelete(cmpmsg);
		return !result;
	}
	return true;
}
