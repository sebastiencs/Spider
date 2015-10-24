#include "paquetKeys.hh"
#include <vector>
#include <map>
#include <Windows.h>

#pragma once
class Packager
{
	std::vector<PaquetKeys *> _pKeys;
	bool shift;
	bool win;
public:
	Packager();
	virtual ~Packager();

	void addKey(int nCode, WPARAM wParam, LPARAM lParam);
};

