#pragma once

#include <Windows.h>

class Startup
{
public:
	Startup();
	~Startup();

	int			isStartup() const;
	void		addStartup(const std::string& ip, const std::string& port);
	void		delStartup();

private:

	std::wstring	_wappPath;
};
