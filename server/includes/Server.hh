//
// server.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 08:40:57 2015 chapui_s
// Last update Wed Oct 21 08:40:57 2015 chapui_s
//

#ifndef SERVER_H_
# define SERVER_H_

# include <boost/cstdint.hpp>
# include <boost/thread.hpp>
# include <memory>
# include <iostream>
# include "Web.hh"
# include "Signal.hh"
# include "debug.hh"

class		Server
{
private:
  std::unique_ptr<Web>	_web;
  boost::thread		_thread;
  Signal		_signal;

  std::map<std::string, std::unique_ptr<PaquetCommandServer *>>	_commands;

public:
  Server(uint16_t);
  virtual ~Server();

  void		start();
  void		stop();
  void		readCommand();
};

#endif /* !SERVER_H_ */
