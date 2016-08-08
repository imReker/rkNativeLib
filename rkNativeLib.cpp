#include "pch.h"
#include "rkNativeLib.h"
#include <fileapi.h>
#include "ShellChromeAPI.h"
#include "Winternal.h"

#include <mmdeviceapi.h> 
#include <endpointvolume.h>
#include <audioclient.h>
#include <Propsys.h>
#include <stdio.h>


using namespace Reker::NativeLib;

uint32 Reker::NativeLib::RKFile::CreateFile(String^ szFileName, uint32 dwDesiredAccess, uint32 dwShareMode, uint32 dwCreationDisposition, uint32 dwFlagsAndAttributes, String^ szFileName2, bool bHard) {
	if (szFileName->Length() == 0)
		throw ref new Platform::InvalidArgumentException(L"Filename incorrect.");
	if (szFileName2->Length() == 0) {
		return (uint32)::CreateFileW(szFileName->Data(), dwDesiredAccess, dwShareMode, NULL, dwCreationDisposition, dwFlagsAndAttributes, NULL);
	} else {
		if (bHard == true) {
			if (CreateHardLinkW(szFileName->Data(), szFileName2->Data(), NULL) != FALSE) {
				return 0;
			} else {
				return GetLastError();
				//String^ szStr = ref new String(L"Operation fail. Error:");
				//throw ref new Platform::Exception(0x80070000 | GetLastError(), L"Operation failed.");
			}
		} else {
			DWORD dwAttr = ::GetFileAttributesW(szFileName2->Data());
			if (dwAttr == INVALID_FILE_ATTRIBUTES) {
				//throw ref new Platform::Exception(0x80070000 | GetLastError(), L"Operation failed.");
			}
			//if (CreateSymbolicLink(szFileName->Data(), szFileName2->Data(), (dwAttr & FILE_ATTRIBUTE_DIRECTORY ? 1 : 0) ) != FALSE) {
			if (::CreateSymbolicLinkW(szFileName->Data(), szFileName2->Data(), 1 ) != FALSE) {
				return 0;
			} else {
				return GetLastError();
				//throw ref new Platform::Exception(0x80070000 | GetLastError(), L"Operation failed.");
			}
		}
	}
	return (uint32)INVALID_HANDLE_VALUE;
}

uint32 Reker::NativeLib::RKFile::GetFileAttributes(String^ szFileName) {
	return ::GetFileAttributesW(szFileName->Data());
}

uint32 Reker::NativeLib::RKFile::SetVolumeMountPoint(String^ szVolumeMountPoint, String^ szVolumeName) {
	return 0;
}

uint32 Reker::NativeLib::RKFile::CreateProcess(String^ szFileName) {
	//return (uint32)ShellExecuteW(NULL, L"Open", szFileName->Data(), NULL, NULL, SW_SHOW);
	STARTUPINFO si = {0};
	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;
	return ::CreateProcessW(szFileName->Data(), NULL, NULL, NULL, FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi);
}

uint32 EnableTokenPrivilege(LPCTSTR szPrivilege) {
	HANDLE hToken = 0;
	TOKEN_PRIVILEGES tkp = {0};
	DWORD dwErr = 0;

	if (!::OpenProcessToken(::GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
		return 0x10000 | GetLastError();
	}

	// Get the LUID for the privilege. 
	if (::LookupPrivilegeValue(NULL, szPrivilege, &tkp.Privileges[0].Luid)) {
		tkp.PrivilegeCount = 1;  // one privilege to set    
		tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

		// Set the privilege for this process. 
		if (!::AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, NULL, NULL)) {
			dwErr = 0x20000 | GetLastError();
			CloseHandle(hToken);
			return dwErr;
		} else {
			CloseHandle(hToken);
			return 0;
		}
	} else {
		dwErr = 0x40000 | GetLastError();
		CloseHandle(hToken);
		return dwErr;
	}
}

uint32 Reker::NativeLib::RKNativeLib::AdjustPrivilege() {
	DWORD dwRet = 0;
	if (dwRet = EnableTokenPrivilege(SE_SECURITY_NAME)) {
		//return 0x80000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_TCB_NAME)) {
		//return 0x40000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_SHUTDOWN_NAME)) {
		//return 0x20000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_CREATE_SYMBOLIC_LINK_NAME)) {
		//return 0x10000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_TAKE_OWNERSHIP_NAME)) {
		//return 0x8000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_LOAD_DRIVER_NAME)) {
		//return 0x4000000 | dwRet;
	}

	if (dwRet = EnableTokenPrivilege(SE_DEBUG_NAME)) {
		//return 0x2000000 | dwRet;
	}
	return dwRet;
}

uint32 Reker::NativeLib::RKRegistry::ReadDWORD(RegistryHive hive, String^ szPath, String^ szValue, uint32* lpData) {
	HKEY hKey = NULL;
	if (szPath->Length() == 0)
		throw ref new Platform::InvalidArgumentException(L"Path incorrect.");

	LPCWSTR szVal = szValue ? szValue->Data() : NULL;
	LSTATUS err = ::RegOpenKeyExW((HKEY)hive, szPath->Data(), 0x0, KEY_SET_VALUE, &hKey);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	DWORD dwLength = sizeof(uint32);
	err = ::RegQueryValueExW(hKey, szVal, 0, NULL, (PBYTE)(lpData), &dwLength);
	::RegCloseKey(hKey);
	return err;
}

uint32 Reker::NativeLib::RKRegistry::WriteDWORD(RegistryHive hive, String^ szPath, String^ szValue, uint32 dwData) {
	HKEY hKey = NULL;
	if (szPath->Length() == 0)
		throw ref new Platform::InvalidArgumentException(L"Path incorrect.");

	LPCWSTR szVal = szValue ? szValue->Data() : NULL;
	LSTATUS err = ::RegOpenKeyExW((HKEY)hive, szPath->Data(), 0x0, KEY_SET_VALUE, &hKey);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	err = ::RegSetValueExW(hKey, szVal, 0, REG_DWORD, (PBYTE)(&dwData), sizeof(uint32));
	::RegCloseKey(hKey);
	return err;
}

uint32 Reker::NativeLib::RKRegistry::ReadString(RegistryHive hive, String^ szPath, String^ szValue, String^ szData) {
	HKEY hKey = NULL;
	if (szPath->Length() == 0)
		throw ref new Platform::InvalidArgumentException(L"Path incorrect.");

	LPCWSTR szVal = szValue ? szValue->Data() : NULL;
	LSTATUS err = ::RegOpenKeyExW((HKEY)hive, szPath->Data(), 0x0, KEY_SET_VALUE, &hKey);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	DWORD dwLength = 0;
	err = ::RegQueryValueExW(hKey, szVal, 0, NULL, NULL, &dwLength);

	err = ::RegQueryValueExW(hKey, szVal, 0, NULL, (PBYTE)(szData->Data()), &dwLength);
	::RegCloseKey(hKey);
	return err;
}

uint32 Reker::NativeLib::RKRegistry::WriteString(RegistryHive hive, String^ szPath, String^ szValue, String^ szData) {
	HKEY hKey = NULL;
	if (szPath->Length() == 0)
		throw ref new Platform::InvalidArgumentException(L"Path incorrect.");

	LPCWSTR szVal = szValue ? szValue->Data() : NULL;
	LSTATUS err = ::RegOpenKeyExW((HKEY)hive, szPath->Data(), 0x0, KEY_SET_VALUE, &hKey);
	if (err != ERROR_SUCCESS) {
		return err;
	}
	err = ::RegSetValueExW(hKey, szVal, 0, REG_SZ, (PBYTE)(szData->Data()), szData->Length());
	::RegCloseKey(hKey);
	return err;
}
	
/*This function equals to:
Shell_LaunchSessionByUri((LPCWORD)szUri->Data());

But Shell_LaunchSessionByUri require LAUNCHSESSION permission that only grant to system apps.
So, I do some research and make this.
It can launch all xap app, but failed on uri of appx.
*/
uint32 Reker::NativeLib::RKShell::LaunchSessionByUri(String^ szUri) {
	typedef struct {
		DWORD count;
		DWORD b;
		DWORD c;
	} INSTANCEID;

	typedef uint32(WINAPI* PLAUNCHSESSION)(UINT taskId, LPCWSTR taskUri, LPBYTE parameterData, UINT parameterDataSize, LPVOID launchSessionCallback);
	typedef uint32(WINAPI* PGETTASKINSTANCEIDS)(LPDWORD taskId, INSTANCEID* lpInstanceID);

	if (LoadLibraryExW == NULL) {
		MEMORY_BASIC_INFORMATION mbi = {0};
		VirtualQuery(VirtualQuery, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		LoadLibraryExW = (PLOADLIBRARYEXW)GetProcAddress((HMODULE)mbi.AllocationBase, "LoadLibraryExW");
		if (LoadLibraryExW == NULL) {
			return 1;
		}
	}

	HMODULE hMod = LoadLibraryExW(L"TaskHostSvcs.dll", NULL, 0);
	PLAUNCHSESSION LaunchSession = (PLAUNCHSESSION)GetProcAddress(hMod, "LaunchSession");
	hMod = LoadLibraryExW(L"EMCLIENT.dll", NULL, 0);
	PGETTASKINSTANCEIDS GetTaskInstanceIDs = (PGETTASKINSTANCEIDS)GetProcAddress(hMod, "GetTaskInstanceIDs");
	uint32 ret;

	INSTANCEID iid = {0};
	DWORD dwTaskId = 0;
	
	iid.count = 1;
	ret = GetTaskInstanceIDs(&dwTaskId, &iid);
	if (ret < 0)
		return ret;

	ret = LaunchSession(dwTaskId, szUri->Data(), NULL, 0, NULL);
	return ret;
}

/*
	This function will not work on wp8.1. All codes are under research to makt it work on 8.1.
*/
default::uint32 Reker::NativeLib::RKShell::AdjustVolume(int32 numberOfSteps) {
	//This work on wp8.0
	/*
	return Shell_AdjustVolume(numberOfSteps);
	*/

	//This should work on 8.1, but failed, why?
/*
	if (LoadLibraryExW == NULL) {
		MEMORY_BASIC_INFORMATION mbi = {0};
		VirtualQuery(VirtualQuery, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		LoadLibraryExW = (PLOADLIBRARYEXW)GetProcAddress((HMODULE)mbi.AllocationBase, "LoadLibraryExW");
		if (LoadLibraryExW == NULL) {
			return -1;
		}
	}

	typedef uint32(WINAPI* PCHANGEVOLUMERELATIVE)(DWORD dwVolume);
	HMODULE hMod = LoadLibraryExW(L"ShellChrome.dll", NULL, 0);

	FARPROC ChangeVolumeRelative = GetProcAddress(hMod, "LaunchShellChromeServer");
	DWORD A = ChangeVolumeRelative();
	ChangeVolumeRelative = GetProcAddress(hMod, "InvokeVolumeUp");
	return ChangeVolumeRelative();
*/

	//Another try, use Win32 method.
	//Some day when I test this code, it seemed like to work, music sound turned to 0
	//but.... never came back again, wtf!
	//So use at your own risk.
	CoInitializeEx(0, 0);
	HRESULT hr;
	IMMDeviceEnumerator* pDeviceEnumerator = 0;
	IMMDevice* pDevice = 0;
	IMMDeviceCollection* pDevices = 0;
	IAudioEndpointVolume* pAudioEndpointVolume = 0;
	IAudioClient* pAudioClient = 0;

	try {
		hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&pDeviceEnumerator);
		if (FAILED(hr)) throw "CoCreateInstance";
		hr = pDeviceEnumerator->EnumAudioEndpoints(eRender, DEVICE_STATE_ACTIVE, &pDevices);
		UINT uCount = 0;
		pDevices->GetCount(&uCount);
		for (int i = 0; i < uCount; i++) {
			pDevices->Item(i, &pDevice);

			//hr = pDeviceEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
			//if (FAILED(hr)) throw "GetDefaultAudioEndpoint";
			hr = pDevice->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_ALL, NULL, (void**)&pAudioEndpointVolume);
			if (FAILED(hr)) throw "pDevice->Active";
			hr = pDevice->Activate(__uuidof(IAudioClient), CLSCTX_ALL, NULL, (void**)&pAudioClient);
			if (FAILED(hr)) throw "pDevice->Active";

			UINT cChannels = 0;
			pAudioEndpointVolume->GetChannelCount(&cChannels);
			for (UINT j = 0; j < cChannels; j++) {


				pAudioEndpointVolume->(j, 0.0, NULL);
			}
			// 
/*

			if (numberOfSteps == -2) {
				hr = pAudioEndpointVolume->SetMute(FALSE, NULL);
				if (FAILED(hr)) throw "SetMute";
			} else if (numberOfSteps == -1) {
				hr = pAudioEndpointVolume->SetMute(TRUE, NULL);
				if (FAILED(hr)) throw "SetMute";
			} else {
				if (numberOfSteps < 0 || numberOfSteps>100) {
					hr = E_INVALIDARG;
					throw "Invalid Arg";
				}

				float fVolume;
				fVolume = numberOfSteps / 100.0f;
				hr = pAudioEndpointVolume->SetMasterVolumeLevelScalar(fVolume, &GUID_NULL);
				if (FAILED(hr)) throw "SetMasterVolumeLevelScalar";


			}*/
		}
		pAudioClient->Release();
		pAudioEndpointVolume->Release();
		pDevice->Release();
		pDeviceEnumerator->Release();
		return true;
	} catch (...) {
		if (pAudioClient) pAudioClient->Release();
		if (pAudioEndpointVolume) pAudioEndpointVolume->Release();
		if (pDevice) pDevice->Release();
		if (pDeviceEnumerator) pDeviceEnumerator->Release();
	}
	return false;
}

default::uint32 Reker::NativeLib::RKShell::RequestShutdown(int32 requestType) {
	return Shell_RequestShutdown((SHUTDOWN_REQUEST_TYPE)requestType);
}

bool Reker::NativeLib::RKShell::IsKidZoneActive() {
	return Shell_IsKidZoneActive();
}

/*
	Try to call directly and skip normal dial UI.
	It's not work, PH_DIAL_PARAMETERS seems use contact's id to make a call.
	Need symbols to go deep into  PhoneDial@phoneom.dll
*/
default::uint32 Reker::NativeLib::RKPhoneOM::PhoneDial(String^ szNumber) {
	return 0;

/*
	typedef struct {
		DWORD dwUnknow;
		LPVOID a[11];
	} PH_DIAL_PARAMETERS;
	typedef uint32(WINAPI* PPHONEDIAL)(PH_DIAL_PARAMETERS* dial, DWORD dwUnknow);

	//static uint32 PhoneDial(String^ szNumber, uint32 dwUnknow);
	//static uint32 PhoneAPIInitialize();
	//static uint32  PhoneAPIUninitialize();
	if (LoadLibraryExW == NULL) {
		MEMORY_BASIC_INFORMATION mbi = {0};
		VirtualQuery(VirtualQuery, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
		LoadLibraryExW = (PLOADLIBRARYEXW)GetProcAddress((HMODULE)mbi.AllocationBase, "LoadLibraryExW");
		if (LoadLibraryExW == NULL) {
			return 1;
		}
	}

	HMODULE hMod = LoadLibraryExW(L"phoneom.dll", NULL, 0);

	FARPROC PhoneAPIInitialize = GetProcAddress(hMod, "PhoneAPIInitialize");
	FARPROC PhoneAPIUninitialize = GetProcAddress(hMod, "PhoneAPIUninitialize");
	PPHONEDIAL PhoneDial = (PPHONEDIAL)GetProcAddress(hMod, "PhoneDial");
	DWORD dwRet = 0;
	dwRet = PhoneAPIInitialize();
	if (dwRet >= 0) {
		PH_DIAL_PARAMETERS dial = {0};
		dial.dwUnknow = 0x100;
		//dial.a[1] = L"10086";
		dial.a[2] = L"10086";
		//dial.a[3] = L"10086";
		PhoneDial(&dial, 0);
		PhoneAPIUninitialize();
	}

	return dwRet;*/
}
