// hookDLL.cpp : Defines the exported functions for the DLL application.
//

#include <stdio.h>
#include <iostream>
#include "hookDLL.h"


extern "C" LRESULT __declspec(dllexport) CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	std::cout << nCode << std::endl;
	return CallNextHookEx(0, nCode, wParam, lParam);
}
