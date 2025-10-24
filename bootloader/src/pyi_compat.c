#include <windows.h>
#include <stdio.h>
#include "pyi_compat.h"

/*
 * Note, designed for modules that are certainly loaded (kernel32.dll etc.), otherwise
 * rewrite to LoadLibrary[/FreeLibrary] instead of GetProcAddress(GetModuleHandleW()).
 */
#define DEFINE_COMPAT_FN(Module, RetType, Name, ArgList, CallList)                     \
                                                                                       \
RetType fallback_##Name ArgList;                                                       \
                                                                                       \
RetType COMPAT_FN(Name) ArgList                                                        \
{                                                                                      \
    typedef RetType (WINAPI *p##Name) ArgList;                                         \
    static p##Name pFunc = NULL;                                                       \
    static int initialized = 0;                                                        \
    if (!initialized) {                                                                \
        pFunc = (p##Name)GetProcAddress(GetModuleHandleA(#Module ".dll"), #Name);      \
        initialized = 1;                                                               \
    }                                                                                  \
    return pFunc ? pFunc CallList : fallback_##Name CallList;                          \
}                                                                                      \
                                                                                       \
RetType fallback_##Name ArgList

DEFINE_COMPAT_FN(kernel32, BOOL, SetDllDirectoryW, (LPCWSTR lpPathName), (lpPathName))
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

DEFINE_COMPAT_FN(kernel32, DWORD, GetFinalPathNameByHandleW, (HANDLE hFile, LPWSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags), (hFile, lpszFilePath, cchFilePath, dwFlags))
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return 0;
}

DEFINE_COMPAT_FN(kernel32, BOOLEAN, CreateSymbolicLinkW, (LPCWSTR lpSymlinkFileName, LPCWSTR lpTargetFileName, DWORD dwFlags), (lpSymlinkFileName, lpTargetFileName, dwFlags))
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

DEFINE_COMPAT_FN(comctl32, HRESULT, LoadIconMetric, (HINSTANCE hinst, PCWSTR pszName, int lims, HICON *phico), (hinst, pszName, lims, phico))
{
    return E_NOTIMPL;
}

DEFINE_COMPAT_FN(user32, BOOL, ShutdownBlockReasonCreate, (HWND hWnd, LPCWSTR pwszReason), (hWnd, pwszReason))
{
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return FALSE;
}

DEFINE_COMPAT_FN(msvcrt, errno_t, _wputenv_s, (const wchar_t *varname, const wchar_t *value_string), (varname, value_string))
{
#define ENV_VAR_MAX_SIZE 33000
    wchar_t tmp[ENV_VAR_MAX_SIZE];
    _snwprintf(tmp, ENV_VAR_MAX_SIZE, L"%s=%s", varname, value_string);
    _wputenv(tmp);

    return 0;
}
