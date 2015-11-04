#include <Windows.h>
#include <iostream>
#include "Startup.hh"

Startup::Startup()
{
	HMODULE		hModule = GetModuleHandle(NULL);

	_wappPath = std::wstring();

	if (hModule)
	{
		WCHAR	path[MAX_PATH];

		GetModuleFileName(hModule, path, MAX_PATH);
		_wappPath = std::wstring(L"\"") + path + std::wstring(L"\"");
	}
}

Startup::~Startup()
{

}

int			Startup::isStartup() const
{
	WCHAR	tmp[MAX_PATH];
	DWORD	size = MAX_PATH;

	if (!RegGetValue(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"Spider", RRF_RT_ANY, NULL, (LPVOID)tmp, &size)
		&& _wappPath.compare(tmp)) {
		return(0);
	}

	if (!RegGetValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"Spider", RRF_RT_ANY, NULL, (LPVOID)tmp, &size)
		&& _wappPath.compare(tmp)) {
		return(0);
	}

	return (1);
}

void		Startup::addStartup()
{
	HKEY	hkey;

	if (!_wappPath.length() || isStartup()) {
		return ;
	}

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey)
		&& RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey)) {
		std::cerr << "Can't open Key" << std::endl;
		return;
	}

	RegDeleteValue(hkey, L"Spider");

	if (RegSetValueEx(hkey, L"Spider", 0, REG_SZ, (LPBYTE)_wappPath.data(), _wappPath.size() * sizeof(WCHAR) + 1)) {
		std::cerr << "Can't set Key";
	}
}

void		Startup::delStartup()
{
	HKEY	hkey;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey)
		&& RegOpenKeyEx(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_ALL_ACCESS, &hkey)) {
		std::cerr << "Can't open Key" << std::endl;
		return;
	}

	RegDeleteValue(hkey, L"Spider");
}
