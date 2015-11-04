//
// server.cpp<src> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:01:22 2015 chapui_s
// Last update Wed Oct 21 09:01:22 2015 chapui_s
//

#include <boost/algorithm/string.hpp>
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

  _commandsSpider["kill"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(6));
  _commandsSpider["pause"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(7));
  _commandsSpider["destroy"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(8));

  _commandsServer["list"] = [this]() -> int { return (_web->listSpider()); };
  _commandsServer["quit"] = [this]() -> int { _web->stop(); return (1); };
  _commandsServer["help"] = [this]() -> int { return (help()); };
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
 _thread.interrupt();
}

void		Server::stop()
{
  _web->stop();
}

int		Server::help()
{
  std::cout << "Available commands:" << std::endl
	    << "\tkill [Spider1 ...]\t\t- Kill spiders" << std::endl
	    << "\tpause [Spider1 ...]\t\t- Pause spiders" << std::endl
	    << "\tdestroy [Spider1 ...]\t\t- Delete spiders from computers" << std::endl
	    << "\tlist\t\t\t\t- List spiders connected" << std::endl
	    << "\tquit\t\t\t\t- Quit server" << std::endl
	    << "\thelp\t\t\t\t- Disp help" << std::endl;
  return (0);
}

void		Server::readCommand()
{
  help();
  try {

    while (1) {

      auto		prompt = [this]() -> int { std::cout << "> "; return (1); };
      std::string	input;
      std::list<std::string> strs;

      while (prompt() && std::getline(std::cin, input)) {

	int	found = 0;

	for (auto &command : _commandsSpider) {


	  if (boost::starts_with(input, command.first)) {

	    boost::split(strs, input, boost::is_any_of("\t "), boost::token_compress_on);
	    strs.pop_front();

	    if (!strs.size()) {
	      _web->sendCommand(command.second);
	    }
	    else {
	      _web->sendCommand(command.second, strs);
	    }
	    found = 1;
	  }
	}

	for (auto &command : _commandsServer) {
	  if (boost::equals(input, command.first)) {
	    command.second();
	    found = 1;
	  }
	}
	if (!found) {
	  std::cout << "Unknown command" << std::endl;
	}
      }
      std::cin.clear();
      std::cout << std::endl;
    }
  }
  catch (const std::exception &e) {
    std::cerr << "Unable to read input: " << e.what() << std::endl;
  }
}
