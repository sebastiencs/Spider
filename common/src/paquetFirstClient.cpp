//
// paquetFirstClient.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:15:05 2015 chapui_s
// Last update Tue Oct 27 12:21:51 2015 bresci_b bresci_b
//

#include "paquetFirstClient.hh"

PaquetFirstClient::PaquetFirstClient()
{
  _parsed = 0;
  _date = 0;
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
  if (_name)
    delete[] _name;
}

void		PaquetFirstClient::setDate(uint32_t date)
{
  _date = date;
  _parsed = 0;
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
  writeData<uint32_t>(ptr, &_date);
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
  _date = readData<uint32_t>(ptr);
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

uint32_t	PaquetFirstClient::getDate()
{
  if (!_parsed) {
    parsePaquetFirstClient();
  }
  return (_date);
}

void		PaquetFirstClient::dumpPaquet()
{
  std::cout << *this;
}


std::ostream	&operator<<(std::ostream &os, PaquetFirstClient &p)
{
  std::string	name = p.getName();

  os << "PaquetFirstClient = { version : " << p.getVersion();
  os << ", SizeName : " << name.size();
  if (name.size())
    os << ", Name : '" << name << "'";
  os << ", Date : " << p.getDate();
  os << " };" << std::endl;
  return (os);
}
