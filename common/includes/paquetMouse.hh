//
// paquetMouse.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 11:51:48 2015 chapui_s
// Last update Thu Oct 15 11:51:48 2015 chapui_s
//

#ifndef PAQUETMOUSE_H_
# define PAQUETMOUSE_H_

# include <iostream>
# include <string>
# include "paquet.hh"

class		PaquetMouse : public Paquet
{
private:
  enum {
    ID = 8,
  };

  uint8_t	_id;
  uint32_t	_date;
  uint16_t	_sizeActive;
  char		*_active;
  uint16_t	_X;
  uint16_t	_Y;
  uint16_t	_pid;
  uint8_t	_button;
  char		_parsed;

  void		parsePaquetMouse();

public:

  PaquetMouse();
  PaquetMouse(const void *, size_t);
  virtual ~PaquetMouse();

  void		setDate(uint32_t);
  void		setActive(const std::string &);
  void		setX(uint16_t);
  void		setY(uint16_t);
  void		setPid(uint16_t);
  void		setButton(uint32_t);

  void		createPaquet();

  uint32_t	getDate();
  char		*getActive();
  uint16_t	getX();
  uint16_t	getY();
  uint16_t	getPid();
  uint8_t	getButton();

  virtual void		dumpPaquet();

};

std::ostream	&operator<<(std::ostream &, PaquetMouse &);

#endif /* !PAQUETMOUSE_H_ */
