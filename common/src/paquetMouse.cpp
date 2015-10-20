//
// paquetMouse.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 11:58:10 2015 chapui_s
// Last update Thu Oct 15 11:58:10 2015 chapui_s
//

#include "paquetMouse.hh"

PaquetMouse::PaquetMouse()
{
  _id = PaquetMouse::ID;
  _parsed = 0;
  _active = 0;
  _sizeActive = 0;
  _date = 0;
  _X = 0;
  _Y = 0;
  _button = 0;
}

PaquetMouse::PaquetMouse(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetMouse::~PaquetMouse()
{
  delete[] _active;
}

void		PaquetMouse::setDate(uint32_t date)
{
  _date = date;
  _parsed = 0;
}

void		PaquetMouse::setActive(const std::string &active)
{
  _sizeActive = active.size();
  _active = new char[_sizeActive + 1]();
  std::copy(active.data(), active.data() + _sizeActive, _active);
  _parsed = 0;
}

void		PaquetMouse::setX(uint16_t X)
{
  _X = X;
  _parsed = 0;
}

void		PaquetMouse::setY(uint16_t Y)
{
  _Y = Y;
  _parsed = 0;
}

void		PaquetMouse::setButton(uint32_t button)
{
  _button = button;
  _parsed = 0;
}

void		PaquetMouse::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint32_t>(ptr, &_date);
  writeData<uint16_t>(ptr, &_sizeActive);
  writeData<char>(ptr, _active, _sizeActive);
  writeData<uint16_t>(ptr, &_X);
  writeData<uint16_t>(ptr, &_Y);
  writeData<uint8_t>(ptr, &_button);
}

void		PaquetMouse::parsePaquetMouse()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _date = readData<uint32_t>(ptr);
  _sizeActive = readData<uint16_t>(ptr);
  if (_sizeActive) {
    delete[] _active;
    _active = new char[_sizeActive + 1]();
    readData<char>(ptr, _active, _sizeActive);
  }
  _X = readData<uint16_t>(ptr);
  _Y = readData<uint16_t>(ptr);
  _button = readData<uint8_t>(ptr);

  _parsed = 1;
}

uint32_t	PaquetMouse::getDate()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  return (_date);
}

char		*PaquetMouse::getActive()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  return (_active);
}

uint16_t	PaquetMouse::getX()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  return (_X);
}

uint16_t	PaquetMouse::getY()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  return (_Y);
}

uint8_t		PaquetMouse::getButton()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  return (_button);
}

void		PaquetMouse::dumpPaquet()
{
  if (!_parsed) {
    parsePaquetMouse();
  }
  std::cout << "PaquetMouse = { date : " << _date << ", sizeActive : " << _sizeActive;
  if (_sizeActive)
    std::cout << ", active : '" << _active << "'";
  std::cout << ", X : " << _X;
  std::cout << ", Y : " << _Y;
  std::cout << ", Button : " << (int)_button;
  std::cout << ((_button == 1) ? ("(Left)") : ((_button == 2) ? ("(Middle)") : ("(Right)")));
  std::cout << " };" << std::endl;
}
