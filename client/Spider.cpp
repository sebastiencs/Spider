#include <Windows.h>
#include <stdio.h>
#include <iostream>


typedef LRESULT(*HookFunction)(int, WPARAM, LPARAM);

HHOOK kHook;
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


extern "C" int main()
	{
	/*	dllHandle = LoadLibrary(TEXT("spiderDLL"));
		if (!dllHandle)
			std::cerr << "LoadLibrary error : " << GetLastError() << std::endl;

		hookAddr = (HookFunction)GetProcAddress(dllHandle, "_KeyboardProc@12");
		if (!hookAddr)
			std::cerr << "getPRocAddress error : " << GetLastError() << std::endl;*/

		//kHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)hookAddr, dllHandle, 0);
		kHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
		if (!kHook)
			std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;

		MSG message;
		while (GetMessage(&message, NULL, 0, 0)) {
			//std::cout << "code key : " << message.wParam << std::endl;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		UnhookWindowsHookEx(kHook);
		return 0;
	}
