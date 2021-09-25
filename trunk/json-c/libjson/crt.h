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

#ifndef _HUGE_ENUF
#define _HUGE_ENUF  1e+300  // _HUGE_ENUF*_HUGE_ENUF must overflow
#endif

#define INFINITY   ((float)(_HUGE_ENUF * _HUGE_ENUF))

#define _DENORM    (-2)
#define _FINITE    (-1)
#define _INFCODE   1
#define _NANCODE   2

#define FP_INFINITE  _INFCODE
#define FP_NAN       _NANCODE
#define FP_NORMAL    _FINITE
#define FP_SUBNORMAL _DENORM
#define FP_ZERO      0

typedef int                 BOOL;

typedef ULONG_PTR HCRYPTPROV;

// dwFlags definitions for CryptAcquireContext
#define CRYPT_VERIFYCONTEXT     0xF0000000
#define CRYPT_NEWKEYSET         0x00000008
#define CRYPT_DELETEKEYSET      0x00000010
#define CRYPT_MACHINE_KEYSET    0x00000020
#define CRYPT_SILENT            0x00000040
#if (NTDDI_VERSION >= NTDDI_VISTA)
#define CRYPT_DEFAULT_CONTAINER_OPTIONAL 0x00000080
#endif //(NTDDI_VERSION >= NTDDI_VISTA)

// certenrolld_begin -- PROV_RSA_*
#define PROV_RSA_FULL           1
#define PROV_RSA_SIG            2
#define PROV_DSS                3
#define PROV_FORTEZZA           4
#define PROV_MS_EXCHANGE        5
#define PROV_SSL                6
#define PROV_RSA_SCHANNEL       12
#define PROV_DSS_DH             13
#define PROV_EC_ECDSA_SIG       14
#define PROV_EC_ECNRA_SIG       15
#define PROV_EC_ECDSA_FULL      16
#define PROV_EC_ECNRA_FULL      17
#define PROV_DH_SCHANNEL        18
#define PROV_SPYRUS_LYNKS       20
#define PROV_RNG                21
#define PROV_INTEL_SEC          22
#if (NTDDI_VERSION >= NTDDI_WINXP)
#define PROV_REPLACE_OWF        23
#define PROV_RSA_AES            24
#endif //(NTDDI_VERSION >= NTDDI_WINXP)
// certenrolld_end

#define LC_ALL          0
#define LC_COLLATE      1
#define LC_CTYPE        2
#define LC_MONETARY     3
#define LC_NUMERIC      4
#define LC_TIME         5

void __cdecl _assert(_In_z_ const char * _Message, _In_z_ const char * _File, _In_ unsigned _Line);

#define assert(_Expression) (void)( (!!(_Expression)) || (_assert(#_Expression, __FILE__, __LINE__), 0) )

//_ACRTIMP int * __cdecl _errno(void){}
//#define errno (*_errno())
//int errno()
//{
//    return *_errno();
//}

int gbl_errno;
#define errno   (gbl_errno)


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

char * strdup(const char * strSource);

__declspec(noalias)
_Check_return_opt_
//_CRT_STDIO_INLINE 
int __CRTDECL fprintf(
    _Inout_                       FILE * const _Stream,
    _In_z_ _Printf_format_string_ char const * const _Format,
    ...);

void * __cdecl calloc(size_t number, size_t size);

int __CRTDECL vfprintf(
    _Inout_                       FILE * const _Stream,
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
);

int __CRTDECL _vscprintf(
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
);

BOOL
__stdcall
CryptAcquireContextA(
    _Out_       HCRYPTPROV * phProv,
    _In_opt_    LPCSTR    szContainer,
    _In_opt_    LPCSTR    szProvider,
    _In_        DWORD       dwProvType,
    _In_        DWORD       dwFlags
);

BOOL
WINAPI
CryptGenRandom(
    _In_                    HCRYPTPROV  hProv,
    _In_                    DWORD   dwLen,
    _Inout_updates_bytes_(dwLen)   BYTE * pbBuffer
);

BOOL
WINAPI
CryptReleaseContext(
    _In_    HCRYPTPROV  hProv,
    _In_    DWORD       dwFlags
);

int __CRTDECL vprintf(
    _In_z_ _Printf_format_string_ char const * const _Format,
    va_list           _ArgList
);

DWORD
WINAPI
GetVersion(
    VOID
);

DWORD
WINAPI
GetLastError(
    VOID
);

time_t __CRTDECL time(_Out_opt_ time_t * const _Time);

int __cdecl _open(_In_z_ const char * _Filename, _In_ int _OpenFlag, ...);

int __cdecl close(_In_ int _FileHandle);

int __cdecl read(int _FileHandle, _Out_writes_bytes_(_MaxCharCount) void * _DstBuf, _In_ unsigned int _MaxCharCount);

int __cdecl write(_In_ int _Filehandle, _In_reads_bytes_(_MaxCharCount) const void * _Buf, _In_ unsigned int _MaxCharCount);

char * __cdecl setlocale(_In_ int _Category, _In_opt_z_ const char * _Locale);

void __cdecl abort(void);

char * __cdecl getenv(_In_z_ const char * _VarName);

char * __cdecl strerror(_In_ int);

double __cdecl nan(_In_ char const * _X);

int    __cdecl _finite(_In_ double _X);
#define isinf(x) (!_finite(x))

int    __cdecl _isnan(_In_ double _X);
#define isnan(x) _isnan(x)

FILE * __cdecl __acrt_iob_func(unsigned _X);

double _HUGE;


//////////////////////////////////////////////////////////////////////////////////////////////////
