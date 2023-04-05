#include <time.h>
#include <stdio.h>
#include <windows.h>
#include <TlHelp32.h>

char *dir;

#define WindowLoop(cls, pid) { HWND lt_tempHwnd = FindWindow(cls, NULL); \
								while (lt_tempHwnd != NULL) { \
									if (pid == GetProcessID(lt_tempHwnd)) { \
										if (GetParent(lt_tempHwnd) == NULL)
#define WindowLoopEnd() } lt_tempHwnd = GetWindow(lt_tempHwnd, GW_HWNDNEXT); }}
#define WindowLoopHandle() lt_tempHwnd

#define ProcessLoop { HANDLE lt_hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); \
						PROCESSENTRY32 lt_pe32 = {0}; \
						lt_pe32.dwSize = sizeof(PROCESSENTRY32); \
						if(Process32First(lt_hProcess, &lt_pe32)) { \
							while(Process32Next(lt_hProcess, &lt_pe32))
#define ProcessLoopEnd() } CloseHandle(lt_hProcess); }
#define ProcessLoopName() lt_pe32.szExeFile
#define ProcessLoopID() lt_pe32.th32ProcessID

ULONG GetProcessID (HWND lp_hwnd) {
	ULONG lv_idProc;
	GetWindowThreadProcessId(lp_hwnd, &lv_idProc);
	return lv_idProc;
}

void CheckWindow (const char* cls, const char* cap) {
	HWND hw = FindWindow(cls, cap);
	char p[MAX_PATH];

	if (hw) {
		sprintf(p,"%d", hw);
		ShellExecute(NULL, "runas", "Terminator.exe", p, dir, SW_SHOW);
		while (IsWindow(hw)) {
			Sleep(1);
		}
	}
}
void CheckWindowBrowser (const char* cls, const char* cap) {
	HWND hw;
	char p[MAX_PATH];
	char txt[MAX_PATH];
	
	ProcessLoop {
		if (strcmp(ProcessLoopName(), "chrome.exe") == 0) {
			WindowLoop(cls, ProcessLoopID()) {
				hw = WindowLoopHandle();
				if (hw) {
					GetWindowText(hw, txt, MAX_PATH);
					if (strstr(txt, cap) != NULL) {
						sprintf(p,"%d", hw);
						ShellExecute(NULL, "runas", "Terminator.exe", p, dir, SW_SHOW);
						while (IsWindow(hw)) {
							Sleep(1);
						}
					}
				}
			} WindowLoopEnd();
		}
	} ProcessLoopEnd();
}

bool BlockTime (int start, int end) {
	time_t t;
	struct tm stm;

	time(&t);
	stm = *localtime(&t);
	if (end >= start) {
		if ((stm.tm_hour >= start) && (stm.tm_hour <= end)) {
			return true;
		}
	} else {
		if ((stm.tm_hour >= start) || (stm.tm_hour <= end)) {
			return true;
		}
	}
	return false;
}

int main (int argc, char* argv[]) {
	*strrchr(argv[0], '\\') = '\0';
	dir = argv[0];

	while (1) {
		if (BlockTime(21, 2)) {
			CheckWindow("WINDOWSCLIENT", "Roblox");
			CheckWindow("UnrealWindow", "VALORANT  ");
			CheckWindowBrowser("Chrome_WidgetWin_1", "YouTube");
		}
		Sleep(1);
	}
	return 0;
}