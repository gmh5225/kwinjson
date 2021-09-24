#pragma once


#include "pch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


#if defined _NO_CRT_STDIO_INLINE
#undef _CRT_STDIO_INLINE
#define _CRT_STDIO_INLINE
#elif !defined _CRT_STDIO_INLINE
#define _CRT_STDIO_INLINE __inline
#endif


#define _CRT_INTERNAL_LOCAL_PRINTF_OPTIONS (*__local_stdio_printf_options())
#define _CRT_INTERNAL_LOCAL_SCANF_OPTIONS  (*__local_stdio_scanf_options ())


#if defined _M_IX86 && !defined _M_HYBRID_X86_ARM64
#define __crt_va_start_a(ap, v) ((void)(ap = (va_list)_ADDRESSOF(v) + _INTSIZEOF(v)))
#elif defined _M_X64
#define __crt_va_start_a(ap, x) ((void)(__va_start(&ap, x)))
#endif

#define __crt_va_start(ap, x) ((void)(__crt_va_start_a(ap, x)))

#define __crt_va_end(ap)        ((void)(ap = (va_list)0))

#define _CRT_GUARDOVERFLOW
#define _ACRTIMP
#define _CRT_HYBRIDPATCHABLE

#define __crt_va_end(ap)        ((void)(ap = (va_list)0))

#define _CRTALLOCATOR __declspec(allocator)


//////////////////////////////////////////////////////////////////////////////////////////////////


int __CRTDECL sscanf(
    _In_z_                       char const * const _Buffer,
    _In_z_ _Scanf_format_string_ char const * const _Format,
    ...);

double __cdecl strtod(const char * strSource, char ** endptr);

__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void __cdecl free(
    _Pre_maybenull_ _Post_invalid_ void * _Block
);

__declspec(noalias)
//_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
//_ACRTIMP _CRTALLOCATOR _CRT_JIT_INTRINSIC _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl malloc(
    _In_ _CRT_GUARDOVERFLOW size_t _Size
);

__declspec(noalias)
//_Success_(return != 0) _Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
//_ACRTIMP _CRTALLOCATOR _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl realloc(
    _Pre_maybenull_ _Post_invalid_ void * _Block,
    _In_ _CRT_GUARDOVERFLOW        size_t _Size
);

//https://docs.microsoft.com/en-us/cpp/dotnet/converting-projects-from-mixed-mode-to-pure-intermediate-language?view=msvc-160
#ifndef __FLTUSED__
#define __FLTUSED__
//extern "C" __declspec(selectany) int _fltused = 1;
extern __declspec(selectany) int _fltused = 1;
#endif

_Success_(return >= 0)
_Check_return_opt_
_CRT_STDIO_INLINE int __CRTDECL _vsnprintf(
    _Out_writes_opt_(_BufferCount) _Post_maybez_ char * const _Buffer,
    _In_                                        size_t      const _BufferCount,
    _In_z_ _Printf_format_string_               char const * const _Format,
    va_list           _ArgList
);


//////////////////////////////////////////////////////////////////////////////////////////////////
