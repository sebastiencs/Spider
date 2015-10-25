#ifndef PACKAGER_H
#define PACKAGER_H


#include <vector>
#include <map>
#include <Windows.h>
#include "paquetKeys.hh"
#include "paquetMouse.hh"
#pragma once
class Packager
{
	std::vector<Paquet *> _paquets;
	bool _shift;
	bool _win;
	bool _ctrl;

public:
	Packager();
	virtual ~Packager();

	void addKey(int nCode, WPARAM wParam, LPARAM lParam);
	void addClick(int nCode, WPARAM wParam, LPARAM lParam);


	Paquet *getPaquet();
	size_t isLeft();
	void supprPaquet();
};

#endif // !PACKAGER_H
