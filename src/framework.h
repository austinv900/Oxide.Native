#pragma once
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#else
#include <unistd.h>
#include <limits.h>
#include <cstring>
#include <errno.h>
#include <sys/stat.h>
#endif