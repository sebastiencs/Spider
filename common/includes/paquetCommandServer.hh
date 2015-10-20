//
// paquetCommandServer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 12:44:23 2015 chapui_s
// Last update Thu Oct 15 12:44:23 2015 chapui_s
//

#ifndef PAQUETCOMMANDSERVER_H_
# define PAQUETCOMMANDSERVER_H_

# include <iostream>
# include "paquet.hh"

class		PaquetCommandServer : public Paquet
{
private:
  enum {
    ID = 2,
  };

  uint8_t	_id;
  uint16_t	_sizeCommand;
  char		*_command;
  char		_parsed;

  void		parsePaquetCommandServer();

public:

  PaquetCommandServer();
  PaquetCommandServer(const void *, size_t);
  virtual ~PaquetCommandServer();

  void		setCommand(const std::string &);

  void		createPaquet();

  char		*getCommand();

  virtual void		dumpPaquet();

};

#endif /* !PAQUETCOMMANDSERVER_H_ */
