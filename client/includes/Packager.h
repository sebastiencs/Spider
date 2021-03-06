#ifndef PACKAGER_H
#define PACKAGER_H


#include <vector>
#include <map>
#include <Windows.h>
#include <boost\interprocess\sync\interprocess_semaphore.hpp>
#include <boost\thread.hpp>
#include <boost\thread\mutex.hpp>
#include "paquetKeys.hh"
#include "paquetMouse.hh"
#include "Tools.hh"

#pragma once
class Packager
{
	std::vector<Paquet *> _paquets;
	bool _lshift;
	bool _rshift;
	bool _lwin;
	bool _rwin;
	bool _lctrl;
	bool _rctrl;
	bool _alt;
	bool _altGr;

	boost::interprocess::interprocess_semaphore	_sem;

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
