#pragma once
#undef LoadLibraryExW
#undef CreateFile
#undef GetFileAttributes
#undef SetVolumeMountPoint
#undef CreateProcess

typedef HMODULE(WINAPI*PLOADLIBRARYEXW)(
	_In_ LPCWSTR lpLibFileName,
	_Reserved_ HANDLE hFile,
	_In_ DWORD dwFlags
	);

PLOADLIBRARYEXW LoadLibraryExW = 0;

namespace Reker {
	namespace NativeLib {
		using namespace Platform;

		public ref class RKFile sealed {
		public:
			static uint32 CreateFile(String^ szFileName, uint32 dwDesiredAccess, uint32 dwShareMode, uint32 dwCreationDisposition, uint32 dwFlagsAndAttributes, String^ szFileName2, bool bHard);
			static uint32 GetFileAttributes(String^ szFileName);
			static uint32 SetVolumeMountPoint(String^ szVolumeMountPoint, String^ szVolumeName);
			static uint32 CreateProcess(String^ szFileName);
		};

		public ref class RKShell sealed {
		public:
			static bool IsKidZoneActive();
			static uint32 LaunchSessionByUri(String^ szUri);
			static uint32 AdjustVolume(int32 numberOfSteps);
			static uint32 RequestShutdown(int32 requestType);
		};

		public enum class RegistryHive {
			HKCR = (int)HKEY_CLASSES_ROOT,
			HKCU = (int)HKEY_CURRENT_USER,
			HKLM = (int)HKEY_LOCAL_MACHINE,
			HKU = (int)HKEY_USERS,
			HKCC = (int)HKEY_CURRENT_CONFIG
		};

		public ref class RKRegistry sealed {
		public:
			static uint32 ReadDWORD(RegistryHive hive, String^ szPath, String^ szValue, uint32* lpData);
			static uint32 WriteDWORD(RegistryHive hive, String^ szPath, String^ szValue, uint32 dwData);
			static uint32 ReadString(RegistryHive hive, String^ szPath, String^ szValue, String^ szData);
			static uint32 WriteString(RegistryHive hive, String^ szPath, String^ szValue, String^ szData);
		};

		public ref class RKPhoneOM sealed {
		public:
			static uint32 PhoneDial(String^ szNumber);
		};

		public ref class RKNativeLib sealed {
		public:
			static uint32 AdjustPrivilege();
		};
	}
}