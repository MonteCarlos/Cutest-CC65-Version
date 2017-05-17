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

#include <stddef.h>

typedef char CuStringChar_t;

typedef struct CuString_tag CuString;

#include "../CuTest.h"

typedef size_t CuStringLen_t;
typedef size_t CuStringSize_t;

/* CuString */

char* CuStrAlloc(size_t size);
char* CuStrCopy(const char* old);
char *CuStrVaFormat(const char* format, va_list va);
char *CuStrFormat(const char* format, ...);

#define CUSTRING_LEN_INC		64
#define CUSTRING_LEN_NEW      64

CuError_t CuStringInit(CuString* str);
CuString* CuStringNew(void);
void CuStringRead(CuString* str, const char* path);
CuString *CuStringAppend(CuString* str, const char* text);
CuError_t CuStringAppendChar(CuString* str, char ch);
CuError_t CuStringAppendFormat(CuString* str, const char* format, ...);
CuError_t CuStringInsert(CuString* str, const char* text, int pos);
CuError_t CuStringResize(CuString* str, size_t newSize);
bool CuStringDelete(CuString* str);
CuStringLen_t CuStringLen(CuString *str);
size_t CuStringSize(CuString *str);
CuError_t CuStringClear(CuString *str);

char* CuStringCStr(CuString* str);
CuError_t CuStringAppendLineFile(CuString* str, char* file, unsigned long int line);
void CuStringComposeMessage(CuString* str, const char* msg1, const char* msg2, const char* file, unsigned long int line);
CuError_t CuStringAppendULong(CuString *str, unsigned long int num);
CuError_t CuStringAppendISvsNOT(CuString *str, const char* format, ...);
CuString* CuStringConvertCStr(const char* text);
CuString *CuStringAppendVariadicFormat(CuString* str, const char* format, va_list va);
/*#define TAGGEDSTRLIST STR(NOMEM, "Not enough mem.")
#define STR(x,y) x,
enum ErrorCodesEnum {CUSTRERR_MIN, TAGGEDSTRLIST};
#undef STR
*/
#endif /* CUTESTSTRING_H */
