#include <Windows.h>
#include <Psapi.h>
#include <boost\date_time\posix_time\posix_time.hpp>
#include "Tools.hh"

uint32_t SelfUtils::secondsSinceEpoch() {
	const boost::posix_time::ptime time = boost::posix_time::microsec_clock::local_time();
	const boost::posix_time::ptime epoch = boost::posix_time::from_time_t(0);
	boost::posix_time::time_duration duration = time - epoch;
	return duration.total_seconds();
}


std::string* SelfUtils::getActiveWindowTitle() {
	TCHAR wnd_title[500];
	HWND hwnd = GetForegroundWindow();
	GetWindowText(hwnd, wnd_title, sizeof(wnd_title));
	std::wstring ws(wnd_title);
	std::string* title = new std::string();
	title->append(ws.begin(), ws.end());
	return title;
}

uint16_t SelfUtils::getActiveWindowPID() {
	HWND hwnd = GetForegroundWindow();
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	return (uint16_t)pid;
}

std::string* SelfUtils::getCleanName(const std::string& fullName) {
	std::string* cleanString = new std::string(fullName);
	if (fullName.length() == 0)
		return cleanString;
	if (fullName.find_last_of("\\") != std::string::npos) {
		*cleanString = fullName.substr(fullName.find_last_of("\\") + 1, fullName.length());
	}
	return cleanString;
}


std::string* SelfUtils::getNameFromPID(uint16_t pid) {
	HANDLE Handle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	std::string* buffer_str = new std::string("");
	if (Handle)
	{
		TCHAR buffer[MAX_PATH];
		buffer[0] = 0;
		if (GetModuleFileNameEx(Handle, 0, buffer, MAX_PATH))
		{
			std::wstring wstr(buffer);
			buffer_str->append(wstr.begin(), wstr.end());
			buffer_str = SelfUtils::getCleanName(*buffer_str);
		}
		CloseHandle(Handle);
	}
	return buffer_str;
}

