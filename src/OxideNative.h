#pragma once

#ifdef _WIN32
#define DLLEXPORT __declspec(dllexport)
#define STDCALL __stdcall
#else
#define DLLEXPORT
#define STDCALL
#endif

extern "C" {
    DLLEXPORT bool STDCALL IsSymbolicLink(const char* path);
    DLLEXPORT bool STDCALL ResolveSymbolicLink(const char* path, char* resolvedPath, int bufferLen, int* resolvedLen);
    DLLEXPORT int STDCALL GetLastErrorCode();
}

enum {
    ERR_NO_ERROR = 0
};