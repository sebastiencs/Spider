#ifndef HOOKDLL_H_
# define HOOKDLL_H_

# include <Windows.h>


extern "C" LRESULT __declspec(dllexport) CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif