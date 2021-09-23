#include "crt.h"
#include "test.h"


#pragma warning(disable:4565) 
#pragma warning(disable:4273) 


_Check_return_ _CRT_INSECURE_DEPRECATE(sscanf_s)
_CRT_STDIO_INLINE int __CRTDECL sscanf(
    _In_z_                       char const * const _Buffer,
    _In_z_ _Scanf_format_string_ char const * const _Format,
    ...)
{
    int _Result;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);
    //_Result = _vsscanf_l(_Buffer, _Format, NULL, _ArgList);
    _Result = sscanf_s(_Buffer, _Format, _ArgList);
    __crt_va_end(_ArgList);
    return _Result;
}


_Success_(return >= 0)
_Check_return_opt_
_CRT_STDIO_INLINE int __CRTDECL sprintf(
    _Pre_notnull_ _Always_(_Post_z_) char * const _Buffer,
    _In_z_ _Printf_format_string_    char const * const _Format,
    ...)
{
    int _Result;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);

    UNREFERENCED_PARAMETER(_Buffer);

    //_Result = _vsprintf_l(_Buffer, _Format, NULL, _ArgList);

    __crt_va_end(_ArgList);
    return _Result;
}


//static
_Check_return_ _Ret_maybenull_ _Post_writable_byte_size_(_Size)
//_ACRTIMP 
//_CRTALLOCATOR _CRT_JIT_INTRINSIC _CRTRESTRICT _CRT_HYBRIDPATCHABLE
void * __cdecl malloc(
    _In_ _CRT_GUARDOVERFLOW size_t _Size
)
{
    UNREFERENCED_PARAMETER(_Size);

    return NULL;
}
