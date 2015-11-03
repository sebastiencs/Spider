#include <Windows.h>
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

