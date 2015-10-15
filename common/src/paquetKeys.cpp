//
// paquetKeys.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 08:57:50 2015 chapui_s
// Last update Thu Oct 15 08:57:50 2015 chapui_s
//

#include <cstring>
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
  this->setData(0, (void *)data, size);
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
  memcpy(_active, active.data(), _sizeActive);
  _parsed = 0;
}

void		PaquetKeys::setText(const std::string &text)
{
  _sizeText = text.size();
  _text = new char[_sizeText + 1]();
  memcpy(_text, text.data(), _sizeText);
  _parsed = 0;
}

void		PaquetKeys::createPaquet()
{
  size_t	ptr;

  ptr = 0;
  this->setData(ptr, &_id, 1);
  ptr += 1;
  this->setData(ptr, &_date, 4);
  ptr += 4;
  this->setData(ptr, &_sizeActive, 2);
  ptr += 2;
  if (_sizeActive) {
    this->setData(ptr, _active, _sizeActive);
    ptr += _sizeActive;
  }
  this->setData(ptr, &_sizeText, 2);
  ptr += 2;
  if (_sizeText) {
    this->setData(ptr, _text, _sizeText);
  }
}

void		PaquetKeys::parsePaquetKeys()
{
  char		*data;
  size_t	ptr;

  data = this->getData();
  ptr = 0;
  memcpy(&_id, data + ptr, 1);
  ptr = 1;
  memcpy(&_date, data + ptr, 4);
  ptr += 4;
  memcpy(&_sizeActive, data + ptr, 2);
  ptr += 2;
  if (_sizeActive) {
    delete[] _active;
    _active = new char[_sizeActive + 1]();
    memcpy(_active, data + ptr, _sizeActive);
    ptr += _sizeActive;
  }
  memcpy(&_sizeText, data + ptr, 2);
  ptr += 2;
  if (_sizeText) {
    delete[] _text;
    _text = new char[_sizeText + 1]();
    memcpy(_text, data + ptr, _sizeText);
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
  if (!_parsed) {
    parsePaquetKeys();
  }
  std::cout << "PaquetKeys = { date : " << _date << ", sizeActive : " << _sizeActive;
  if (_sizeActive)
    std::cout << ", active : '" << _active << "'";
  std::cout << ", sizeText : " << _sizeText;
  if (_sizeText)
    std::cout << ", text : '" << _text << "'";
  std::cout << " };" << std::endl;
}
