#pragma once

#define COMPAT_FN(fn)  compat_##fn

BOOL COMPAT_FN(SetDllDirectoryW)(LPCWSTR lpPathName);

DWORD COMPAT_FN(GetFinalPathNameByHandleW)(HANDLE hFile, LPWSTR lpszFilePath, DWORD cchFilePath, DWORD dwFlags);

#define SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE 0x2
BOOLEAN COMPAT_FN(CreateSymbolicLinkW)(LPCWSTR lpSymlinkFileName, LPCWSTR lpTargetFileName, DWORD dwFlags);

#define LIM_LARGE 1
HRESULT COMPAT_FN(LoadIconMetric)(HINSTANCE hinst, PCWSTR pszName, int lims, HICON *phico);

BOOL COMPAT_FN(ShutdownBlockReasonCreate)(HWND hWnd, LPCWSTR pwszReason);

errno_t COMPAT_FN(_wputenv_s)(const wchar_t *varname, const wchar_t *value_string);
