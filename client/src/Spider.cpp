#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Hooker.hh"
#include "reseau/Network.hh"

int main()
{
//	Hooker& hooker = Hooker::getInstance();
	Network* network = new Network("4242", "10.41.174.3");
	network->initNetwork();
	network->write("coucou!", 7);
	while (1) {
		network->write("coucou!", 7);
	}
	//hooker.runHookLoop();
}
