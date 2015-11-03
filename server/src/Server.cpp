//
// server.cpp<src> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:01:22 2015 chapui_s
// Last update Wed Oct 21 09:01:22 2015 chapui_s
//

#include <boost/algorithm/string/predicate.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "Server.hh"

Server::Server(uint16_t port)
  : _web(new Web(port)),
    _signal(*this)
{
  DEBUG_MSG("Server is running");
  boost::filesystem::create_directory("Logs");
  _signal.addSignal(SIGINT);

  _commands["kill"] = new PaquetCommandServer(2);
}

Server::~Server()
{
  DEBUG_MSG("Closing server");

  _thread.detach();
}

void		Server::start()
{
  try {
    _thread = boost::thread(&Server::readCommand, this);
  }
  catch (const std::exception &e) {
    std::cerr << "Unable to run thread: " << e.what() << std::endl;
  }
 _web->start();
 // _web->stop();
}

void		Server::stop()
{
  _web->stop();
}

void		Server::readCommand()
{
  std::cout << "Available commands:" << std::endl
	    << "\tkill\t\t- Kill spiders" << std::endl
	    << "\tpause\t\t- Pause spiders" << std::endl
	    << "\tdestroy\t\t- Delete spiders from computers" << std::endl;
  try {
    while (1) {
      std::string	input;

      while (std::getline(std::cin, input)) {
	std::cout << "READ: '" << input << "'\n";

	if (boost::starts_with(input, "kill ")) {
	  std::cout << "KILL DETECTED\n";
	}

	_web->sendCommand();
	// Envoie des commandes aux clients
      }
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Unable to read input: " << e.what() << std::endl;
  }
}
