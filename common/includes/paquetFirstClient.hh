//
// paquetFirstClient.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:12:41 2015 chapui_s
// Last update Thu Oct 15 13:12:41 2015 chapui_s
//

#ifndef PAQUETFIRSTCLIENT_H_
# define PAQUETFIRSTCLIENT_H_

# include <iostream>
# include <string>
# include "paquet.hh"

class		PaquetFirstClient : public Paquet
{
private:

  uint32_t	_date;
  uint16_t	_version;
  uint16_t	_sizeName;
  char		*_name;
  char		_parsed;

  void		parsePaquetFirstClient();

public:

  PaquetFirstClient();
  PaquetFirstClient(const void *, size_t);
  virtual ~PaquetFirstClient();

  void		setVersion(uint16_t);
  void		setDate(uint32_t);
  void		setName(const std::string &);

  void		createPaquet();

  uint32_t	getDate();
  uint8_t	getVersion();
  char		*getName();

  virtual void		dumpPaquet();

};

std::ostream	&operator<<(std::ostream &, PaquetFirstClient &);

#endif /* !PAQUETFIRSTCLIENT_H_ */
