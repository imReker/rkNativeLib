#pragma once

typedef struct _MESSAGETOASTDATA {
	GUID  productId;   // Used for setting the notification glow and retrieving the icon
	PWSTR pszText1;    // Display string
	PWSTR pszText2;    // Display string
	PWSTR pszTaskUri;  // Executed when the notification is clicked
	PWSTR pszSound;    // the event sound that will play when this toast is displayed
} MESSAGETOASTDATA, *LPMESSAGETOASTDATA;

/// <summary>
///     Displays a toast style message in the chrome.
/// </summary>
/// <param name="pMessageToastData">
///     Contains the various fields to control the display of the toast
/// </param>
/// <returns>
///     HRESULT
/// </returns>
HRESULT WINAPI Shell_PostMessageToast(LPMESSAGETOASTDATA pMessageToastData);

#define LPCWORD WORD CONST *
HRESULT WINAPI DiagnosticHook_GetCurrentShellState(PULONG);
HRESULT WINAPI Shell_AddOverlay(LPCWORD);
HRESULT WINAPI Shell_AdjustVolume(INT numberOfSteps);
HRESULT WINAPI Shell_CreateAutomation(ULONG);
HRESULT WINAPI Shell_CreateReminder(LPVOID, struct ReminderConfig *, struct ReminderAction *);
HRESULT WINAPI Shell_DeInitReminders(LPVOID);
HRESULT WINAPI Shell_DeleteReminder(LPVOID, LPGUID);
HRESULT WINAPI Shell_FindFirstReminder(LPVOID, ULONG, LPVOID *, LPGUID, struct ReminderData * *);
HRESULT WINAPI Shell_FindNextReminder(LPVOID, ULONG, LPVOID, LPGUID, struct ReminderData * *);
HRESULT WINAPI Shell_FindReminderClose(LPVOID, LPVOID *);
//enum DEVICE_LOCK_TYPE WINAPI Shell_GetCurrentLockState(VOID);
//enum SHELL_MODE_TYPE WINAPI Shell_GetCurrentMode(VOID);
HRESULT WINAPI Shell_GetCurrentWallpaper(LPWSTR);
HRESULT WINAPI Shell_GetLockGraceTime(PULONG);
HRESULT WINAPI Shell_GetReminderData(LPVOID, LPCGUID, struct ReminderData * *);
HRESULT WINAPI Shell_GetScreenIdleTime(PULONG);
HRESULT WINAPI Shell_GetValidLockGraceTimesList(PULONG, PULONG);
HRESULT WINAPI Shell_GetValidScreenIdleList(PULONG, PULONG);
HRESULT WINAPI Shell_IdleTimerReset(ULONG);
HRESULT WINAPI Shell_InitReminders(LPVOID *);
HRESULT WINAPI Shell_IsActiveWallpaperProvider(INT *);
INT WINAPI Shell_IsKidZoneActive(VOID);
INT WINAPI Shell_IsKidZoneEnabled(VOID);
INT WINAPI Shell_IsLockPasswordSet(VOID);
INT WINAPI Shell_IsLocked(VOID);
INT WINAPI Shell_IsUnlockedNormal(VOID);
HRESULT WINAPI Shell_LaunchSessionByUri(LPCWORD);
HRESULT WINAPI Shell_LaunchSessionByUriEx(LPCWORD);
HRESULT WINAPI Shell_LaunchSessionByUriReset(LPCWORD);
HRESULT WINAPI Shell_LaunchWalletSessionByUri(LPCWORD);
HRESULT WINAPI Shell_Lock(VOID);
HRESULT WINAPI Shell_LockAndShowKidZoneLock(VOID);
HRESULT WINAPI Shell_NavigateToErrorPageOnPinShellTileFailureInKidZone(VOID);
HRESULT WINAPI Shell_RaiseGameAchievementMessageToast(struct _MESSAGETOASTDATA *);
HRESULT WINAPI Shell_RefreshLockLASSData(VOID);
HRESULT WINAPI Shell_RefreshLockScreenNotifications(VOID);
HRESULT WINAPI Shell_RegisterButtonPressCallback(enum ShellButton, struct IButtonHandler *);
HRESULT WINAPI Shell_ReleaseReminderData(LPVOID, struct ReminderData *);
HRESULT WINAPI Shell_RemoveOverlay(LPCWORD);
HRESULT WINAPI Shell_RequestShutdown(enum SHUTDOWN_REQUEST_TYPE);
HRESULT WINAPI Shell_SetAsActiveWallpaperProvider(INT *);
HRESULT WINAPI Shell_SetCurrentKidZoneWallpaper(LPCWORD);
HRESULT WINAPI Shell_SetCurrentWallpaper(LPCWORD, INT);
HRESULT WINAPI Shell_SetDebugOverlay(LPCWORD);
HRESULT WINAPI Shell_SetHardwareButtonRestrictedState(enum HARDWARE_BUTTON_RESTRICTED_STATE);
HRESULT WINAPI Shell_SetKidZoneDisplayName(LPCWORD);
HRESULT WINAPI Shell_SetLockGraceTime(ULONG);
HRESULT WINAPI Shell_SetLockScreenAlarmIndication(INT);
HRESULT WINAPI Shell_SetReminderState(LPVOID, LPGUID, INT);
HRESULT WINAPI Shell_SetScreenIdleTime(ULONG);
HRESULT WINAPI Shell_SetShowNowPlayingMediaArt(INT);
HRESULT WINAPI Shell_SetTestScene(LPCWORD);
HRESULT WINAPI Shell_SuppressSimPinUI(VOID);
HRESULT WINAPI Shell_TurnScreenOn(INT);
HRESULT WINAPI Shell_Unlock(VOID);
HRESULT WINAPI Shell_UnregisterButtonPressCallback(enum ShellButton, struct IButtonHandler *);
HRESULT WINAPI Shell_UpdateAuthenticationData(struct AUTHENTICATION_STATE_DATA *, LPCWORD, LPCWORD, struct AUTHENTICATION_TYPE_DATA *);
HRESULT WINAPI TestHook_GetCurrentDeviceLockTypes(PULONG, PULONG);