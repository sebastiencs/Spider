//
// paquetFirstClient.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:15:05 2015 chapui_s
// Last update Thu Oct 15 13:15:05 2015 chapui_s
//

#include "paquetFirstClient.hh"

PaquetFirstClient::PaquetFirstClient()
{
  _parsed = 0;
  _version = 0;
  _name = 0;
  _sizeName = 0;
}

PaquetFirstClient::PaquetFirstClient(const void *data, size_t size)
{
  this->setData(0, (void *)data, size);
  _parsed = 0;
}

PaquetFirstClient::~PaquetFirstClient()
{
  delete[] _name;
}

void		PaquetFirstClient::setVersion(uint16_t version)
{
  _version = version;
  _parsed = 0;
}

void		PaquetFirstClient::setName(const std::string &name)
{
  _sizeName = name.size();
  _name = new char[_sizeName + 1]();
  memcpy(_name, name.data(), _sizeName);
  _parsed = 0;
}

void		PaquetFirstClient::createPaquet()
{
  size_t	ptr;

  ptr = 0;
  this->setData(ptr, &_version, 2);
  ptr += 2;
  this->setData(ptr, &_sizeName, 2);
  ptr += 2;
  if (_sizeName) {
    this->setData(ptr, _name, _sizeName);
  }
}

void		PaquetFirstClient::parsePaquetFirstClient()
{
  char		*data;
  size_t	ptr;

  data = this->getData();
  ptr = 0;
  memcpy(&_version, data + ptr, 2);
  ptr = 2;
  memcpy(&_sizeName, data + ptr, 2);
  ptr = 2;
  if (_sizeName) {
    delete[] _name;
    _name = new char[_sizeName + 1]();
    memcpy(_name, data + ptr, _sizeName);
  }
  _parsed = 1;
}

uint8_t		PaquetFirstClient::getVersion()
{
  if (!_parsed) {
    parsePaquetFirstClient();
  }
  return (_version);
}

char		*PaquetFirstClient::getName()
{
  if (!_parsed) {
    parsePaquetFirstClient();
  }
  return (_name);
}

void		PaquetFirstClient::dumpPaquet()
{
  if (!_parsed) {
    parsePaquetFirstClient();
  }
  std::cout << "PaquetFirstClient = { version : " << _version;
  std::cout << ", SizeName : " << _sizeName;
  if (_sizeName)
    std::cout << ", Name : '" << _name << "'";
  std::cout << " };" << std::endl;
}
