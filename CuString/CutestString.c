#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//#include <math.h>

#include "CutestString_internal.h"

/*-------------------------------------------------------------------------*
 * CuStr
 *-------------------------------------------------------------------------*/





/*-------------------------------------------------------------------------*
 * CuString
 *-------------------------------------------------------------------------*/








void CuStringAppendULong(CuString *str, unsigned long int num){
	char numStr[20];
	sprintf(numStr, "%lu", num);
	CuStringAppend(str, numStr);
}

void CuStringInit(CuString* str)
{
	str->length = 0;
	str->size = STRING_MAX;
	str->buffer = (char*) malloc(sizeof(char) * str->size);
	assert(str->buffer != NULL);
	str->buffer[0] = '\0';
}

void CuStringClear(CuString *str){
	if (str->buffer){
		free(str->buffer);
		CuStringInit(str);
	}
}

CuString* CuStringNew(void)
{
	CuString* str = (CuString*) malloc(sizeof(CuString));
	assert(NULL!=str);
	CuStringInit(str);

	return str;
}

CuString* CuStringConvertCStr(char* text){
    CuString *str = CuStringNew();
    CuStringAppend(str, text);//NULL is handled by Append
    return str;
}

void CuStringDelete(CuString *str)
{
	if (!str) return;
	assert(NULL != str->buffer);
	free(str->buffer);
	assert(NULL != str);
	free(str);
}

// TODO (Stefan#1#): does not adjust str->length which maintains the length of the unallocated previous string
void CuStringResize(CuString* str, int newSize)
{
	str->buffer = (char*) realloc(str->buffer, sizeof(char) * newSize);
	assert(str->buffer != NULL);
	str->size = newSize;
}

void CuStringAppend(CuString* str, const char* text)
{
	int length;

	if (text == NULL) {
		text = "NULL";
	}

	length = strlen(text);
	if (str->length + length + 1 >= str->size)
		CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
	str->length += length;
	strcat(str->buffer, text);
}

void CuStringAppendChar(CuString* str, char ch)
{
	char text[2];
	if ('\0' != ch){
		text[0] = ch;
		text[1] = '\0';
		CuStringAppend(str, text);
	}//do not append termination character
}

void CuStringAppendFormat(CuString* str, const char* format, ...)
{
	va_list argp;
	char *buf = (char*)calloc(HUGE_STRING_LEN, sizeof(char));
	assert (NULL != buf);
	va_start(argp, format);
	vsprintf(buf, format, argp);
	va_end(argp);
	CuStringAppend(str, buf);
	assert(NULL != buf);
	free(buf);
}

void CuStringInsert(CuString* str, const char* text, int pos)
{
	int length = strlen(text);
	if (pos > str->length)
		pos = str->length;
	if (str->length + length + 1 >= str->size)
		CuStringResize(str, str->length + length + 1 /*+ STRING_INC*/);
	memmove(str->buffer + pos + length, str->buffer + pos, (str->length - pos) + 1);
	str->length += length;
	memcpy(str->buffer + pos, text, length);
}

