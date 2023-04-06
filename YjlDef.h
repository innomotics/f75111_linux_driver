#ifndef __YJLDEF_H__
#define __YJLDEF_H__

#ifdef CST
#undef CST
#endif
#define CST

//typedef static inline	INL;

typedef unsigned long long U64;
typedef signed   long long S64;

typedef unsigned int U32;
typedef signed   int S32;


typedef unsigned short U16;
typedef signed   short S16;

typedef unsigned char U8;
typedef signed   char S8;

typedef int BOOL;


//typedef unsigned long    u32;        // u32      = unsigned long

typedef void*	HANDLE;

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE    0
#endif

#define VOID void

#define MemSet memset
#define MemMalloc malloc
#define Assert assert
#define MemCopy memcpy
#define MemCpy memcpy	// used by HuffPack
#define MemFree free
#define MemReAlloc realloc
#define MemCmp memcmp
#define Swap(a, b) {U32 t; t=a;a=b;b=t;}
#define MemZero(a,b) memset(a, 0x00, b)

#define WIDEN2(X) L##X
#define WIDEN(X) WIDEN2(X)
#define __WDATE__  WIDEN(__DATE__)
#define __WTIME__  WIDEN(__TIME__)

typedef struct
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int fraction;

} TIMESTAMP_STRUCT;
/*
unsigned long long GetDateTimeByU64(void);
unsigned int GetDateTimeByU32(void);
void ConvDateTime (U32, TIMESTAMP_STRUCT*);
unsigned long long ConvDateTime(TIMESTAMP_STRUCT*, U64);
void GetTime(wchar_t*);
FILE* wfopen(const wchar_t*, const char*);
//ConvDateTime (timeval32, &timest);
//timeval64 = ConvDateTime (&timest, timeval64);
*/
#endif

