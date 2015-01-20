#ifndef CUTESTSTRING_H
#define CUTESTSTRING_H

#define CUSTRING_VERSION  "CuString 1.5"

#define CUSTRID(x) x
#define CUSTRINGIFY(x) #x
#define SAVECUSTRINGIFY(x) CUSTRINGIFY(x)
#define __LINESTR__ SAVECUSTRINGIFY(CUSTRID(__LINE__))

#ifdef __CC65__
    #pragma charmap(92, 47)
#endif // __CC65__

typedef size_t CuStringLen_t;
typedef size_t CuStringSize_t;
typedef char CuStringChar_t;

typedef struct CuString_tag CuString;

#include "..\CuTest.h"

/* CuString */

char* CuStrAlloc(int size);
char* CuStrCopy(const char* old);



#define HUGE_STRING_LEN	512
#define STRING_MAX		256
#define STRING_INC		256

void CuStringInit(CuString* str);
CuString* CuStringNew(void);
void CuStringRead(CuString* str, const char* path);
void CuStringAppend(CuString* str, const char* text);
void CuStringAppendChar(CuString* str, char ch);
void CuStringAppendFormat(CuString* str, const char* format, ...);
void CuStringInsert(CuString* str, const char* text, int pos);
void CuStringResize(CuString* str, int newSize);
void CuStringDelete(CuString* str);
CuStringLen_t CuStringlen(CuString *str);
CuStringSize_t CuStringsize(CuString *str);
int CuStringClear(CuString *str);

char* CuStringCStr(CuString* str);
void CuStringAppendLineFile(CuString* str, char* file, unsigned long int line);
void CuStringComposeMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line);
void CuStringAppendULong(CuString *str, unsigned long int num);
int CuStringAppendISvsNOT(CuString *str, const char* format, ...);
CuString* CuStringConvertCStr(const char* text);
void CuStringAppendVariadicFormat(CuString* str, const char* format, va_list va);
/*#define TAGGEDSTRLIST STR(NOMEM, "Not enough mem.")
#define STR(x,y) x,
enum ErrorCodesEnum {CUSTRERR_MIN, TAGGEDSTRLIST};
#undef STR
*/
#endif /* CUTESTSTRING_H */
