#include "crt.h"
#include "pch.h"
#include "../cJSON/cJSON.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


//__declspec(noalias)
//_Check_return_ _CRT_INSECURE_DEPRECATE(sscanf_s)
//_CRT_STDIO_INLINE 
int __CRTDECL sscanf(
    _In_z_                       char const * const _Buffer,
    _In_z_ _Scanf_format_string_ char const * const _Format,
    ...)
{
    int _Result = 0;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);

    //_Result = _vsscanf_l(_Buffer, _Format, NULL, _ArgList);
    _Result = sscanf_s(_Buffer, _Format, _ArgList);

    __crt_va_end(_ArgList);
    return _Result;
}


//_Check_return_
//_ACRTIMP double __cdecl strtod(
//    _In_z_                   char const * _String,
//    _Out_opt_ _Deref_post_z_ char ** _EndPtr
//) 
double __cdecl strtod(const char * strSource, char ** endptr)
/*
需要自己实现，驱动一般不用浮点数。
要用浮点数还得一些特殊的代码技巧。

参考：\Win2K3\NT\base\crts\crtw32\convert\strtod.c
*/
{
    UNREFERENCED_PARAMETER(strSource);
    UNREFERENCED_PARAMETER(endptr);

    return 0;
}


__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void __cdecl free(
    _Pre_maybenull_ _Post_invalid_ void * _Block
)
{
    if (_Block) {
        ExFreePoolWithTag(_Block, TAG);
    }
}


__declspec(noalias)
//_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
//_ACRTIMP _CRTALLOCATOR _CRT_JIT_INTRINSIC _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl malloc(
    _In_ _CRT_GUARDOVERFLOW size_t _Size
)
{
    return ExAllocatePoolWithTag(PagedPool, _Size, TAG);
}


__declspec(noalias)
//_Success_(return != 0) _Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
//_ACRTIMP _CRTALLOCATOR _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl realloc(
    _Pre_maybenull_ _Post_invalid_ void * _Block,
    _In_ _CRT_GUARDOVERFLOW        size_t _Size
)
/*
这里要有复制操作。

另一个思路是禁用realloc函数，如：global_hooks.reallocate = NULL;
或者声明realloc函数的地址是null.

一般断定：新申请的内存大小大于原来的内存的大小。

cjson.c中有两处使用allocate的地方。
这里两处都有个else的处理，即hooks->reallocate == NULL
其中一处：硬编码buffer->length == 256.
另一处假定：newsize >= p->offset + 1.
*/
{
    void * ret = malloc(_Size);
    if (!ret) {
        return ret;
    }

    memset(ret, 0, _Size);

    if (_Block) {
        memcpy(ret, _Block, min(256, _Size));
        free(_Block);
    }

    return ret;
}


//typedef __declspec(noalias) void *  (__cdecl * realloc_fn)(void * _Block, size_t _Size);
// realloc_fn  realloc;
//__declspec(noalias) void * (__cdecl * realloc)(void * _Block, size_t _Size);


//https://docs.microsoft.com/en-us/cpp/dotnet/converting-projects-from-mixed-mode-to-pure-intermediate-language?view=msvc-160
#ifndef __FLTUSED__
#define __FLTUSED__
//extern "C" __declspec(selectany) int _fltused = 1;
//__declspec(selectany) int _fltused = 1;
#endif


//使用的工程加入这个：
//TARGETLIBS = $(DDK_LIB_PATH)\libcntpr.lib


//////////////////////////////////////////////////////////////////////////////////////////////////
