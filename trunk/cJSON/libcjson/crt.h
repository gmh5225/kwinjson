#pragma once


#include "test.h"


#pragma warning(disable:4565) 
#pragma warning(disable:4273) 


#if defined _NO_CRT_STDIO_INLINE
#undef _CRT_STDIO_INLINE
#define _CRT_STDIO_INLINE
#elif !defined _CRT_STDIO_INLINE
#define _CRT_STDIO_INLINE __inline
#endif


#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS (*__local_stdio_printf_options())
#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS  (*__local_stdio_scanf_options ())


#define __crt_va_start(ap, x) __crt_va_start_a(ap, x)


#define __crt_va_start_a(ap, x) ((void)(__va_start(&ap, x)))
#define __crt_va_arg(ap, t)                                               \
        ((sizeof(t) > sizeof(__int64) || (sizeof(t) & (sizeof(t) - 1)) != 0) \
            ? **(t**)((ap += sizeof(__int64)) - sizeof(__int64))             \
            :  *(t* )((ap += sizeof(__int64)) - sizeof(__int64)))
#define __crt_va_end(ap)        ((void)(ap = (va_list)0))


#define _CRTALLOCATOR __declspec(allocator)

#define _CRT_HYBRIDPATCHABLE

#define _CRT_GUARDOVERFLOW


//////////////////////////////////////////////////////////////////////////////////////////////////


//void * __cdecl malloc(
//    _In_ _CRT_GUARDOVERFLOW size_t _Size
//);

