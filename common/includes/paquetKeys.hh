//
// paquetKeys.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 08:49:15 2015 chapui_s
// Last update Thu Oct 15 08:49:15 2015 chapui_s
//

#ifndef PAQUETKEYS_H_
# define PAQUETKEYS_H_

# include <vector>
# include <string>
# include "vk_codes.hh"
# include "paquet.hh"

class		PaquetKeys : public Paquet
{
private:
  enum {
    ID = 1,
  };

  uint8_t	_id;
  uint32_t	_date;
  uint16_t	_sizeActive;
  uint16_t	_pid;
  char		*_active;
  uint16_t	_sizeText;
  char		*_text;
  char		*_textDecoded;
  char		_parsed;

  void		parsePaquetKeys();

public:

  PaquetKeys();
  PaquetKeys(const void *, size_t);
  virtual ~PaquetKeys();

  void		setDate(uint32_t);
  void		setPid(uint16_t);
  void		setActive(const std::string &);
  void		setText(const std::string &);
  void		setText(const std::vector<uint8_t> &);

  void		createPaquet();

  uint32_t	getDate();
  char		*getActive();
  char		*getText();
  char		*getTextDecoded();
  uint16_t	getPid();

  virtual void		dumpPaquet();

};

std::ostream	&operator<<(std::ostream &, PaquetKeys &);

#endif /* !PAQUETKEYS_H_ */
