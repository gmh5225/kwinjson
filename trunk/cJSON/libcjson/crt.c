#include "crt.h"


#pragma warning(disable:4996)  //'ExAllocatePoolWithTag': ExAllocatePoolWithTag is deprecated, use ExAllocatePool2.


//////////////////////////////////////////////////////////////////////////////////////////////////


//__declspec(noalias)
_Check_return_ _CRT_INSECURE_DEPRECATE(sscanf_s)
//_CRT_STDIO_INLINE 
int __CRTDECL sscanf(
    _In_z_                       char const * const _Buffer,
    _In_z_ _Scanf_format_string_ char const * const _Format,
    ...
)
{
    int _Result = 0;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);

    //_Result = _vsscanf_l(_Buffer, _Format, NULL, _ArgList);
    _Result = sscanf_s(_Buffer, _Format, _ArgList);

    __crt_va_end(_ArgList);
    return _Result;
}


_Check_return_ _ACRTIMP
double __cdecl strtod(
    _In_z_                   char const * _String,
    _Out_opt_ _Deref_post_z_ char ** _EndPtr
) 
/*
需要自己实现，驱动一般不用浮点数。
要用浮点数还得一些特殊的代码技巧。

参考：\Win2K3\NT\base\crts\crtw32\convert\strtod.c
*/
{
    UNREFERENCED_PARAMETER(_String);
    UNREFERENCED_PARAMETER(_EndPtr);

    ASSERTMSG("本工程在驱动下暂不支持浮点数。", FALSE);

    return 0;
}


__declspec(noalias)
_ACRTIMP _CRT_HYBRIDPATCHABLE
void __cdecl free(
    _Pre_maybenull_ _Post_invalid_ void * _Block
)
{
    if (_Block) {
        PJSON_POOL p = CONTAINING_RECORD(_Block, JSON_POOL, Pool);
        ExFreePoolWithTag(p, TAG);
    }
}


__declspec(noalias)
_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
_ACRTIMP _CRTALLOCATOR _CRT_JIT_INTRINSIC _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl malloc(
    _In_ _CRT_GUARDOVERFLOW size_t _Size
)
{
    if (0 == _Size) {
        return NULL;
    }

    void * ret = ExAllocatePoolWithTag(PagedPool, _Size + FIELD_OFFSET(JSON_POOL, Pool), TAG);
    if (NULL == ret) {
        return ret;
    }

    //memset(ret, 0, _Size + FIELD_OFFSET(JSON_POOL, Pool));//未来优化应该去掉此行。未来便于排错应该加上此行。

    PJSON_POOL temp = (PJSON_POOL)ret;

    temp->NumberOfBytes = _Size;

    return (PBYTE)ret + FIELD_OFFSET(JSON_POOL, Pool); // sizeof(SIZE_T)
}


__declspec(noalias)
_Success_(return != 0) _Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
_ACRTIMP _CRTALLOCATOR _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl realloc(
    _Pre_maybenull_ _Post_invalid_ void * _Block,
    _In_ _CRT_GUARDOVERFLOW        size_t _Size
)
/*
这里要有复制操作。

另一个思路是禁用realloc函数，如：global_hooks.reallocate = NULL;
或者声明realloc函数的地址是null.

一般用法是断定：新申请的内存大小大于原来的内存的大小。

必须解决：原来内存的大小问题。这里采用是一个封装的结构:JSON_POOL.

必须释放原来的内容，因为调用代码中已经设置为NULL了。
*/
{
    void * ret = malloc(_Size);
    if (!ret) {
        return ret;
    }

    memset(ret, 0, _Size);

    if (_Block) {
        PJSON_POOL p = CONTAINING_RECORD(_Block, JSON_POOL, Pool);
        memcpy(ret, _Block, min(p->NumberOfBytes, _Size));//只能取两者的最小者，否则都可能内存越界。
        free(_Block);
    }

    return ret;
}


//typedef void *  (__cdecl * realloc_fn)(void * _Block, size_t _Size);
// realloc_fn  realloc;


//https://docs.microsoft.com/en-us/cpp/dotnet/converting-projects-from-mixed-mode-to-pure-intermediate-language?view=msvc-160
//#ifndef __FLTUSED__
//#define __FLTUSED__
////extern "C" __declspec(selectany) int _fltused = 1;
////__declspec(selectany) int _fltused = 1;//另一个解决思路：在使用的工程加入$(DDK_LIB_PATH)\libcntpr.lib.
//#endif


//////////////////////////////////////////////////////////////////////////////////////////////////
