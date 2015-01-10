#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*-------------------------------------------------------------------------*
 * CuStr
 *-------------------------------------------------------------------------*/
CuStringLen_t CuStringlen(CuString *str){
    assert(str -> length == strlen(str -> buffer));
    //Assert that length field is identical to length of string in buffer

	return str -> length;
}
