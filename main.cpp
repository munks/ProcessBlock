#include <time.h>
#include <stdio.h>
#include <windows.h>

char* dir;
int checkbool = 0;

#define c_YouTube 1

void CheckWindow (const char* cls, const char* cap) {
	HWND hw = FindWindow(cls, cap);
	char p[260];
	
	if (hw) {
		sprintf(p,"%d", hw);
		printf("%d\n", ShellExecute(NULL, "runas", "Terminator.exe", p, dir, SW_SHOW));
		while (IsWindow(hw)) {
			Sleep(1);
		}
	}
}
void CheckWindowBrowser (const char* cls, const char* cap, int idtf) {
	HWND hw = FindWindow(cls, NULL);
	char p[260];
	char txt[260];
	
	if (checkbool & (1 << (idtf - 1))) {
		return;
	}
	if (hw) {
		GetWindowText(hw, txt, 260);
		if (strstr(txt, cap) != NULL) {
			sprintf(p,"%d %d", hw, idtf);
			printf("%d\n", ShellExecute(NULL, "runas", "Terminator.exe", p, dir, SW_SHOW));
			while (IsWindow(hw)) {
				Sleep(1);
			}
		}
	}
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

DWORD WINAPI CheckLoop (LPVOID param) {
	while (1) {
		if (BlockTime(22, 2)) {
			CheckWindow("WINDOWSCLIENT", "Roblox");
			CheckWindow("UnrealWindow", "VALORANT  ");
			CheckWindowBrowser("Chrome_WidgetWin_1", "YouTube", c_YouTube);
		}
		Sleep(1);
	}
	return 0;
}

LRESULT CALLBACK WindowProc (HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	unsigned int ltemp = (unsigned int)lParam;
	switch (uMsg) {
		case WM_COMMAND: {
			if (ltemp > 0) {
				checkbool |= 1 << (ltemp - 1);
			}
			break;
		}
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow) {
	dir = pCmdLine;

	WNDCLASSEX wc = {};

	wc.cbSize = sizeof(wc);
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = "Terminator";
	
	RegisterClassEx(&wc);

	CreateWindow("Terminator", "ASDF", 0, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);
	CreateThread(NULL, 0, CheckLoop, NULL, 0, NULL);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}