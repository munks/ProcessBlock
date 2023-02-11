#include <time.h>
#include <stdio.h>
#include <windows.h>

#define CheckWindow(cls, cap) 	{HWND hw = FindWindow(cls, cap); \
									if (hw) { \
										sprintf(p,"%d", hw); \
										printf("%d\n", ShellExecute(NULL, "runas", "Terminator.exe", p, argv[0], SW_SHOW)); \
										while (IsWindow(hw)) { \
											Sleep(1); \
										} \
									} \
								}


//Custom strstr Function (Reverse)
char* rstrstr (char *str1, const char *str2) {
	char *cp = str1;
	char *s1, *s2;

	if (!*str2) return str1;

	while (*cp) {
		s1 = cp;
		s2 = (char *) str2;
		while (*s1 && *s2 && !(*s1 - *s2)) {
			s1--;
			s2++;
		}
		if (!*s2) return s1;
		cp--;
	}

	return NULL;
}

int main (int argc, char* argv[]) {
	char p[260];
	time_t t;
	struct tm stm;
	
	*(rstrstr(&argv[0][strlen(argv[0])-1], "\\")+1) = '\0';
	
	while (1) {
		time(&t);
		stm = *localtime(&t);
		if ((stm.tm_hour >= 22) || (stm.tm_hour <= 2)) { 
			CheckWindow("WINDOWSCLIENT", "Roblox");
			CheckWindow("UnrealWindow", "VALORANT  ");
		}
		Sleep(1);
	}
	return 0;
}