//
// paquetCommands.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 12:48:10 2015 chapui_s
// Last update Tue Oct 27 12:21:37 2015 bresci_b bresci_b
//

#include "paquetCommandServer.hh"

PaquetCommandServer::PaquetCommandServer()
{
  _id = PaquetCommandServer::ID;
  _parsed = 0;
  _reponse = 0;
}

PaquetCommandServer::PaquetCommandServer(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetCommandServer::PaquetCommandServer(uint8_t reponse)
{
  _id = PaquetCommandServer::ID;
  _parsed = 0;
  _reponse = reponse;
  createPaquet();
}

PaquetCommandServer::~PaquetCommandServer()
{
}

void		PaquetCommandServer::setReponse(uint8_t reponse)
{
  _reponse = reponse;
  _parsed = 0;
}

void		PaquetCommandServer::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_reponse);
}

void		PaquetCommandServer::parsePaquetCommandServer()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _reponse = readData<uint8_t>(ptr);
  _parsed = 1;
}

uint8_t		PaquetCommandServer::getReponse()
{
  if (!_parsed) {
    parsePaquetCommandServer();
  }
  return (_reponse);
}

void		PaquetCommandServer::dumpPaquet()
{
  std::cout << *this;
}

std::ostream	&operator<<(std::ostream &os, PaquetCommandServer &p)
{
  os << "PaquetCommandServer = { reponse : " << (int)p.getReponse();
  os << " };" << std::endl;
  return (os);
}
