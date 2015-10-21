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

class		Server
{
public:
  Server(uint16_t);
  virtual ~Server();

  void		start();
  void		readInput();
};

#endif /* !SERVER_H_ */
