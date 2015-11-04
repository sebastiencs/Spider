#pragma once

#include <Windows.h>

class Startup
{
public:
	Startup();
	~Startup();

	int			isStartup() const;
	void		addStartup();
	void		delStartup();

private:

	std::wstring	_wappPath;
};
