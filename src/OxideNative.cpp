#include "pch.h"
#include "OxideNative.h"

#ifdef _WIN32
__declspec(thread) static int lastErrorCode = ERR_NO_ERROR;
#else
__thread static int lastErrorCode = ERR_NO_ERROR;
#endif

bool STDCALL IsSymbolicLink(const char* path) {
#ifdef _WIN32
	DWORD attributes = GetFileAttributesA(path);
	if (attributes == INVALID_FILE_ATTRIBUTES) {
		lastErrorCode = static_cast<int>(GetLastError());
	}
	return (attributes != INVALID_FILE_ATTRIBUTES) && (attributes & FILE_ATTRIBUTE_REPARSE_POINT);
#else
	struct stat buf;
	if (lstat(path, &buf) != 0) {
		return false;
	}
	return S_ISLNK(buf.st_mode);
#endif
}

bool STDCALL ResolveSymbolicLink(const char* path, char* resolvedPath, int bufferLen, int* resolvedLen) {
#ifdef _WIN32
	const HANDLE h_file = CreateFileA(path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h_file == INVALID_HANDLE_VALUE) {
		return false;
	}
	DWORD length = GetFinalPathNameByHandleA(h_file, resolvedPath, bufferLen, FILE_NAME_NORMALIZED);
	CloseHandle(h_file);
	if (length > 0 && length < static_cast<DWORD>(bufferLen)) {
		*resolvedLen = static_cast<int>(length);
		return true;
	}
	else {
		return false;
	}
#else
	ssize_t length = readlink(path, resolvedPath, bufferLen - 1);
	if (length > 0 && length < bufferLen) {
		resolvedPath[length] = '\0';
		*resolvedLen = length;
		return true;
	}
	else {
		return false;
	}
#endif
}

int STDCALL GetLastErrorCode() {
	return lastErrorCode;
}