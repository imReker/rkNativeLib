//
// pch.h
// Header for standard system include files.
//

#pragma once
#define _ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE 1
#define WINAPI_FAMILY WINAPI_FAMILY_DESKTOP_APP
//#define WINAPI_FAMILY WINAPI_FAMILY_APP
#define _WIN32_WINNT 0x0602
#define LoadLibraryExW __LoadLibraryExW
#include <windows.h>