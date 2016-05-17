
#include "CutestString_internal.h"

const char* CuStrNULL(const char* str){
	if (NULL == str){
        //str = CuStrAlloc(strlen(constStr_NULL));//create new instance of String "NULL"
		//return strcpy(str, constStr_NULL);//constStr_NULL; //copy from lib with const strings
        return constStr_NULL;
	}
	return (char*)str;
}
