#include "crt.h"
#include "pch.h"


//////////////////////////////////////////////////////////////////////////////////////////////////


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
{
    if (_Block) {
        ExFreePoolWithTag(_Block, TAG);
    }

    return ExAllocatePoolWithTag(PagedPool, _Size, TAG);
}


//https://docs.microsoft.com/en-us/cpp/dotnet/converting-projects-from-mixed-mode-to-pure-intermediate-language?view=msvc-160
#ifndef __FLTUSED__
#define __FLTUSED__
//extern "C" __declspec(selectany) int _fltused = 1;
__declspec(selectany) int _fltused = 1;
#endif


_Success_(return >= 0)
_Check_return_opt_
_CRT_STDIO_INLINE int __CRTDECL _vsnprintf(
    _Out_writes_opt_(_BufferCount) _Post_maybez_ char * const _Buffer,
    _In_                                        size_t      const _BufferCount,
    _In_z_ _Printf_format_string_               char const * const _Format,
    va_list           _ArgList
)
{
    return _vsnprintf_l(_Buffer, _BufferCount, _Format, NULL, _ArgList);
}


__declspec(noalias)
_Check_return_
_ACRTIMP 
long long __cdecl strtoll(
    _In_z_                   char const * _String,
    _Out_opt_ _Deref_post_z_ char ** _EndPtr,
    _In_                     int         _Radix
)
{
    UNREFERENCED_PARAMETER(_String);
    UNREFERENCED_PARAMETER(_EndPtr);
    UNREFERENCED_PARAMETER(_Radix);

    return 0;
}


__declspec(noalias)
_Check_return_
_ACRTIMP 
unsigned long long __cdecl strtoull(
    _In_z_                   char const * _String,
    _Out_opt_ _Deref_post_z_ char ** _EndPtr,
    _In_                     int         _Radix
)
{
    UNREFERENCED_PARAMETER(_String);
    UNREFERENCED_PARAMETER(_EndPtr);
    UNREFERENCED_PARAMETER(_Radix);

    return 0;
}


char * strdup(const char * strSource)
{
    UNREFERENCED_PARAMETER(strSource);

    return 0;
}


__declspec(noalias)
_Check_return_opt_
//_CRT_STDIO_INLINE //禁止内敛，否者，使用者找不到这个函数。
int __CRTDECL fprintf(
    _Inout_                       FILE * const _Stream,
    _In_z_ _Printf_format_string_ char const * const _Format,
    ...)
{
    int _Result = 0;
    va_list _ArgList;
    __crt_va_start(_ArgList, _Format);

    //_Result = _vfprintf_l(_Stream, _Format, NULL, _ArgList);
    //_Result = vsprintf_s(_Stream, _Format, NULL, _ArgList);

    __crt_va_end(_ArgList);
    return _Result;
}


void * __cdecl calloc(size_t number, size_t size)
{
    UNREFERENCED_PARAMETER(number);
    UNREFERENCED_PARAMETER(size);

    return 0;
}


//_Check_return_opt_
//_CRT_STDIO_INLINE 
int __CRTDECL vfprintf(
    _Inout_                       FILE * const _Stream,
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
)
{
    UNREFERENCED_PARAMETER(_Stream);
    UNREFERENCED_PARAMETER(_Format);
    UNREFERENCED_PARAMETER(_ArgList);

    return 0;
}


//_Check_return_
//_CRT_STDIO_INLINE 
int __CRTDECL _vscprintf(
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
)
{
    UNREFERENCED_PARAMETER(_Format);
    UNREFERENCED_PARAMETER(_ArgList);

    return 0;
}


BOOL
__stdcall
CryptAcquireContextA(
    _Out_       HCRYPTPROV * phProv,
    _In_opt_    LPCSTR    szContainer,
    _In_opt_    LPCSTR    szProvider,
    _In_        DWORD       dwProvType,
    _In_        DWORD       dwFlags
)
{
    UNREFERENCED_PARAMETER(phProv);
    UNREFERENCED_PARAMETER(szContainer);
    UNREFERENCED_PARAMETER(szProvider);
    UNREFERENCED_PARAMETER(dwProvType);
    UNREFERENCED_PARAMETER(dwFlags);

    return 0;
}


BOOL
WINAPI
CryptGenRandom(
    _In_                    HCRYPTPROV  hProv,
    _In_                    DWORD   dwLen,
    _Inout_updates_bytes_(dwLen)   BYTE * pbBuffer
)
{
    UNREFERENCED_PARAMETER(hProv);
    UNREFERENCED_PARAMETER(dwLen);
    UNREFERENCED_PARAMETER(pbBuffer);

    return 0;
}


BOOL
WINAPI
CryptReleaseContext(
    _In_    HCRYPTPROV  hProv,
    _In_    DWORD       dwFlags
)
{
    UNREFERENCED_PARAMETER(hProv);
    UNREFERENCED_PARAMETER(dwFlags);

    return 0;
}


int __CRTDECL vprintf(
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
)
{
    UNREFERENCED_PARAMETER(_Format);
    UNREFERENCED_PARAMETER(_ArgList);

    return 0;
}


DWORD
WINAPI
GetVersion(
    VOID
)
{
    return 0;
}


DWORD
WINAPI
GetLastError(
    VOID
)
{
    return 0;
}


//static __inline 
time_t __CRTDECL time(
    _Out_opt_ time_t * const _Time
)
{
    //return _time64(_Time);
    return 0;
}


int __cdecl _open(_In_z_ const char * _Filename, _In_ int _OpenFlag, ...)
{
    UNREFERENCED_PARAMETER(_Filename);
    UNREFERENCED_PARAMETER(_OpenFlag);

    return 0;
}


int __cdecl close(_In_ int _FileHandle)
{
    UNREFERENCED_PARAMETER(_FileHandle);

    return 0;
}


int __cdecl read(int _FileHandle, 
                 _Out_writes_bytes_(_MaxCharCount) void * _DstBuf, 
                 _In_ unsigned int _MaxCharCount)
{
    UNREFERENCED_PARAMETER(_FileHandle);
    UNREFERENCED_PARAMETER(_DstBuf);
    UNREFERENCED_PARAMETER(_MaxCharCount);

    return 0;
}


int __cdecl write(_In_ int _Filehandle, 
                  _In_reads_bytes_(_MaxCharCount) const void * _Buf,
                  _In_ unsigned int _MaxCharCount)
{
    UNREFERENCED_PARAMETER(_Filehandle);
    UNREFERENCED_PARAMETER(_Buf);
    UNREFERENCED_PARAMETER(_MaxCharCount);

    return 0;
}


char * __cdecl setlocale(_In_ int _Category, _In_opt_z_ const char * _Locale)
{
    UNREFERENCED_PARAMETER(_Category);
    UNREFERENCED_PARAMETER(_Locale);

    return 0;
}


void __cdecl _assert(_In_z_ const char * _Message, _In_z_ const char * _File, _In_ unsigned _Line)
{
    UNREFERENCED_PARAMETER(_Message);
    UNREFERENCED_PARAMETER(_File);
    UNREFERENCED_PARAMETER(_Line);
}


void __cdecl abort(void)
{

}


char * __cdecl getenv(_In_z_ const char * _VarName)
{
    UNREFERENCED_PARAMETER(_VarName);
    return 0;
}


char * __cdecl strerror(_In_ int error)
{
    UNREFERENCED_PARAMETER(error);
    return 0;
}


double __cdecl nan(_In_ char const * _X)
{
    UNREFERENCED_PARAMETER(_X);
    return 0;
}


int    __cdecl _finite(_In_ double _X)
{
    UNREFERENCED_PARAMETER(_X);
    return 0;
}


int    __cdecl _isnan(_In_ double _X)
{
    UNREFERENCED_PARAMETER(_X);
    return 0;
}





//////////////////////////////////////////////////////////////////////////////////////////////////
