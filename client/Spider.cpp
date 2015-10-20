#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "hookDLL.h"

typedef LRESULT(*HookFunction)(int, WPARAM, LPARAM);

HHOOK kHook;
HINSTANCE dllHandle;
HookFunction hookAddr;

int main()
{
	dllHandle = LoadLibrary(TEXT("hookDLL"));
	if (!dllHandle)
		std::cerr << "LoadLibrary error : " << GetLastError() << std::endl;

	hookAddr = (HookFunction)GetProcAddress(dllHandle, "KeyboardProc");
	if (!hookAddr)
		std::cerr << "getPRocAddress error : " << GetLastError() << std::endl;

	kHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)hookAddr, dllHandle, NULL);
	if (!kHook)
		std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;

	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	UnhookWindowsHookEx(kHook);
	return 0;
}

