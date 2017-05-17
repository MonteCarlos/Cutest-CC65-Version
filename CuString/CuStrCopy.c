#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/** \brief allocates memory for duplication of c-string and then copies the content of the original c-string to the new address
 *
 * \param CuStringSize_t size
 * \return char* strPtr
 *
 */
char* CuStrCopy(const char* old)
{
	if (old){
		char* newStr; //= CuAlloc(strlen(old)+1);//CuStrAlloc(len + 1);

		assert(NULL != old);
		newStr = CuStrAlloc(strlen(old));
		strcpy(newStr, old);
		return newStr;
	}
	return NULL;
}
