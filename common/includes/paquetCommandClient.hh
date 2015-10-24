//
// paquetCommandClient.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 12:44:23 2015 chapui_s
// Last update Thu Oct 15 12:44:23 2015 chapui_s
//

#ifndef PAQUETCOMMANDCLIENT_H_
# define PAQUETCOMMANDCLIENT_H_

# include <iostream>
# include <string>
# include "paquet.hh"

class		PaquetCommandClient : public Paquet
{
private:
  enum {
    ID = 4,
  };

  uint8_t	_id;
  uint8_t	_ok;
  uint16_t	_sizeData;
  char		*_dataReponse;
  char		_parsed;

  void		parsePaquetCommandClient();

public:

  PaquetCommandClient();
  PaquetCommandClient(const void *, size_t);
  virtual ~PaquetCommandClient();

  void		setOk(uint16_t);
  void		setDataReponse(const std::string &);

  void		createPaquet();

  uint8_t	getOk();
  char		*getDataReponse();

  virtual void		dumpPaquet();

};

std::ostream	&operator<<(std::ostream &, PaquetCommandClient &);

#endif /* !PAQUETCOMMANDCLIENT_H_ */
