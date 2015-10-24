//
// server.cpp<src> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:01:22 2015 chapui_s
// Last update Wed Oct 21 09:01:22 2015 chapui_s
//

#include <iostream>
#include "Server.hh"

Server::Server(uint16_t port)
  : _web(new Web(port)),
    _signal(*this)
{
  DEBUG_MSG("Server is running");
  _signal.addSignal(SIGINT);
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
  try {
    while (1) {
      std::string	input;

      while (std::getline(std::cin, input)) {
	std::cout << "READ: '" << input << "'\n";
	// Envoie des commandes aux clients
      }
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Unable to read input: " << e.what() << std::endl;
  }
}
