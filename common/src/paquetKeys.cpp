//
// paquetKeys.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 08:57:50 2015 chapui_s
// Last update Thu Oct 15 08:57:50 2015 chapui_s
//

#include "paquetKeys.hh"

PaquetKeys::PaquetKeys()
{
  _id = PaquetKeys::ID;
  _parsed = 0;
  _text = 0;
  _active = 0;
  _sizeText = 0;
  _sizeActive = 0;
  _date = 0;
}

PaquetKeys::PaquetKeys(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetKeys::~PaquetKeys()
{
  delete[] _text;
  delete[] _active;
}

void		PaquetKeys::setDate(uint32_t date)
{
  _date = date;
  _parsed = 0;
}

void		PaquetKeys::setActive(const std::string &active)
{
  _sizeActive = active.size();
  _active = new char[_sizeActive + 1]();
  std::copy(active.data(), active.data() + _sizeActive, _active);
  _parsed = 0;
}

void		PaquetKeys::setText(const std::string &text)
{
  _sizeText = text.size();
  _text = new char[_sizeText + 1]();
  std::copy(text.data(), text.data() + _sizeText, _text);
  _parsed = 0;
}

void		PaquetKeys::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint32_t>(ptr, &_date);
  writeData<uint16_t>(ptr, &_sizeActive);
  writeData<char>(ptr, _active, _sizeActive);
  writeData<uint16_t>(ptr, &_sizeText);
  writeData<char>(ptr, _text, _sizeText);
}

void		PaquetKeys::parsePaquetKeys()
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
  _sizeText = readData<uint16_t>(ptr);
  if (_sizeText) {
    delete[] _text;
    _text = new char[_sizeText + 1]();
    readData<char>(ptr, _text, _sizeText);
  }
  _parsed = 1;
}

uint32_t	PaquetKeys::getDate()
{
  if (!_parsed) {
    parsePaquetKeys();
  }
  return (_date);
}

char		*PaquetKeys::getActive()
{
  if (!_parsed) {
    parsePaquetKeys();
  }
  return (_active);
}

char		*PaquetKeys::getText()
{
  if (!_parsed) {
    parsePaquetKeys();
  }
  return (_text);
}

void		PaquetKeys::dumpPaquet()
{
  std::cout << *this;
}

std::ostream	&operator<<(std::ostream &os, PaquetKeys &p)
{
  std::string	active = p.getActive();
  std::string	text = p.getText();

  os << "PaquetKeys = { date : " << p.getDate() << ", sizeActive : " << active.size();
  if (active.size())
    os << ", active : '" << active << "'";
  os << ", sizeText : " << text.size();
  if (text.size())
    os << ", text : '" << text << "'";
  os << " };" << std::endl;
  return (os);
}
