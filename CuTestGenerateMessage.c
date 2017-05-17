#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CuString/CutestString.h"

CuError_t CuTestGenerateMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line){
	//CuStringClear(str);
	if (str){
		CuStringAppend(str, file);
		CuStringAppendChar(str, '(');
		CuStringAppendULong(str, line);
		CuStringAppendChar(str, ')');
		//CuStringAppendFormat(str, "%s(%lu)", file, line);

		/*CuStringAppend(str, file);
		CuStringAppendChar(str, '(');
		CuStringAppendULong(str, line);
		CuStringAppendChar(str, ')');
		*/
		if (NULL != msg1){
			CuStringAppendFormat(str, ", %s", msg1);
			//CuStringAppend(str, msg1);
		}

		if (NULL != msg2){
			//CuStringAppend(str, ", ");
			CuStringAppend(str, msg2);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}
