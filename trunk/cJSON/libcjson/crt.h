/*


注意：
1.在驱动下:cJSON.c的print_number函数的length = sprintf((char*)number_buffer, "%1.15g", d);
  得到的只有一个g而不是浮点数。
  即使加上KeSaveExtendedProcessorState和KeRestoreExtendedProcessorState，也是依旧。
2.cjson里的说有数字都是浮点数内部处理。
3.不建议在驱动下使用浮点数，包括整数。
*/


#pragma once


#include "pch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


typedef struct _JSON_POOL {
    SIZE_T NumberOfBytes;
    BYTE Pool[0];
} JSON_POOL;
typedef JSON_POOL * PJSON_POOL;


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
