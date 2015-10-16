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
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
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
  std::copy(name.data(), name.data() + _sizeName, _name);
  _parsed = 0;
}

void		PaquetFirstClient::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint16_t>(ptr, &_version);
  writeData<uint16_t>(ptr, &_sizeName);
  writeData<char>(ptr, _name, _sizeName);
}

void		PaquetFirstClient::parsePaquetFirstClient()
{
  size_t	ptr = 0;

  _version = readData<uint16_t>(ptr);
  _sizeName = readData<uint16_t>(ptr);
  if (_sizeName) {
    delete[] _name;
    _name = new char[_sizeName + 1]();
    readData<char>(ptr, _name, _sizeName);
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
