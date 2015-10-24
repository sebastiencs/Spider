#include <Windows.h>
#include <stdio.h>
#include <iostream>


typedef LRESULT(*HookFunction)(int, WPARAM, LPARAM);

HHOOK kHook;
HHOOK mHook;
HINSTANCE dllHandle;
HookFunction hookAddr;

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0) {
		std::cout << nCode << std::endl;
		std::cout << wParam << std::endl;
		std::cout << ((KBDLLHOOKSTRUCT *)lParam)->vkCode << std::endl;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode >= 0) {
		std::cout << nCode << std::endl;
		std::cout << wParam << std::endl;
		std::cout << ((KBDLLHOOKSTRUCT *)lParam)->vkCode << std::endl;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

int main()
{
	kHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	if (!kHook)
		std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;
	mHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
	if (!mHook)
		std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
	UnhookWindowsHookEx(kHook);
	UnhookWindowsHookEx(mHook);
	return 0;
}
