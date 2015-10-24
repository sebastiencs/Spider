#ifndef PACKAGER_H
#define PACKAGER_H

#include "paquetKeys.hh"
#include <vector>
#include <map>
#include <Windows.h>

class Packager
{
	std::vector<PaquetKeys *> _pKeys;
	bool _shift;
	bool _win;
	bool _ctrl;

public:
	Packager();
	virtual ~Packager();

	void addKey(int nCode, WPARAM wParam, LPARAM lParam);
};

#endif // !PACKAGER_H
