//
// paquetFirstServer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:12:41 2015 chapui_s
// Last update Thu Oct 15 13:12:41 2015 chapui_s
//

#ifndef PAQUETFIRSTSERVER_H_
# define PAQUETFIRSTSERVER_H_

# include <iostream>
# include "paquet.hh"

class		PaquetFirstServer : public Paquet
{
private:

  uint8_t	_reponse;
  char		_parsed;

  void		parsePaquetFirstServer();

public:

  PaquetFirstServer();
  PaquetFirstServer(const void *, size_t);
  virtual ~PaquetFirstServer();

  void		setReponse(uint8_t);

  void		createPaquet();

  uint8_t	getReponse();

  virtual void		dumpPaquet();

};

std::ostream	&operator<<(std::ostream &, PaquetFirstServer &);

#endif /* !PAQUETFIRSTSERVER_H_ */
