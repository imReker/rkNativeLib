# rkNativeLib

Most codes in this library I think is rubbish now.
Something maybe useful:

1.Get restricted LoadLibraryExW with only 2 lines of code.
```
VirtualQuery(VirtualQuery, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
LoadLibraryExW = (PLOADLIBRARYEXW)GetProcAddress((HMODULE)mbi.AllocationBase, "LoadLibraryExW");
```
2.Execute Shell_LaunchSessionByUri without any granted permission on Windows Phone 8&8.1.
```
See Reker::NativeLib::RKShell::LaunchSessionByUri(String^ szUri)
```

Things like change volume are under research and maybe never update again because Windows 10 Mobile are released.
