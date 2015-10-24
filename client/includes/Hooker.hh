#ifndef HOOKER_HH_
# define HOOKER_HH__

# include <Windows.h>
# include <iostream>

class Hooker {
protected:
	HHOOK _kHook;
	HHOOK _mHook;
	bool _connected;
	//Network* _network;

public:
	static Hooker& getInstance();

	void runHookLoop();
	bool initializeHooks();
	void deInitializeHooks();
	void receiveCallback(int nCode, WPARAM wParam, LPARAM lParam, bool isMouse = false);
	bool connect();

	bool& isConnected();
	//Network& getNetwork();

protected:
	Hooker();
	~Hooker();
};

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);

#endif /* !HOOKER_HH_ */
