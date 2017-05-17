#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"
/** \brief Frees memory associated with given CuString.
 *
 * \param CuString* str
 * \return success of free'ing of memory
 *
 */

bool CuStringDelete(CuString *str)
{
    if (str){
		bool freeresult;
		freeresult = (str!=NULL);
		assert(NULL != str);
		assert(NULL != str->buffer);
		freeresult &= CuFree(str->buffer);
		assert(true == freeresult);
		freeresult &= CuFree(str);
		assert(true == freeresult);
		return freeresult;
	}
	return false;
}
