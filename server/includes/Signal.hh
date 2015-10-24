//
// Signal.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Oct 23 13:45:18 2015 chapui_s
// Last update Fri Oct 23 13:45:18 2015 chapui_s
//

#ifndef SIGNAL_H_
# define SIGNAL_H_

# include <boost/enable_shared_from_this.hpp>
# include <functional>
# include <map>

class		Server;

class		Signal
{
private:
  Server	&_server;

public:
  Signal(Server &);
  virtual ~Signal();

  void		addSignal(int);
  void		stopAll();
};

void		sig_handler(int);
Signal		*class_save(int id, Signal *ptr_class);

#endif /* !SIGNAL_H_ */
