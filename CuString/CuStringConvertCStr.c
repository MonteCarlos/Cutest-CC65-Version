#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

CuString* CuStringConvertCStr(char* text){
    CuString *str = CuStringNew();
    CuStringAppend(str, text);//NULL is handled by Append
    return str;
}
