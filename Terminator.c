#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define c_YouTube 1

int main (int argc, char* argv[]) {
	HWND hw = (HWND)atoi(argv[1]);
	HANDLE hd;
	DWORD pid;
	
	if (argc == 2) {
		GetWindowThreadProcessId(hw, &pid);
		hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		TerminateProcess(hd, 0);
		CloseHandle(hd);
		MessageBoxW(NULL, L"10시 강제 종료", L"게임", MB_OK | MB_SYSTEMMODAL);
	}
	if (argc == 3) {
		GetWindowThreadProcessId(hw, &pid);
		hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
		TerminateProcess(hd, 0);
		CloseHandle(hd);
		MessageBoxW(NULL, L"10시 강제 종료", L"YouTube", MB_OK | MB_SYSTEMMODAL);
	}
	return 0;
}