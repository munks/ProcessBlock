#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main (int argc, char* argv[]) {
	HWND hw = (HWND)atoi(argv[1]);
	HANDLE hd;
	DWORD pid;
	
	if (argc == 1) { return 0; }
	GetWindowThreadProcessId(hw, &pid);
	hd = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	TerminateProcess(hd, 0);
	CloseHandle(hd);
	MessageBoxW(NULL, L"10시 강제 종료", L"게임", MB_OK | MB_SYSTEMMODAL);
	return 0;
}