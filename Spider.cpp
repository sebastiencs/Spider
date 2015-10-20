#include <Windows.h>
#include <stdio.h>

HHOOK kHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	printf("%d\n", nCode);
	return CallNextHookEx(kHook, nCode, wParam, lParam);
}

int main()
{
	kHook = SetWindowsHookEx(WH_KEYBOARD, KeyboardProc, nullptr, NULL);
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(kHook);
	return 0;
}

