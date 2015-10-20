//
// paquetFirstServer.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:15:05 2015 chapui_s
// Last update Thu Oct 15 13:15:05 2015 chapui_s
//

#include "paquetFirstServer.hh"

PaquetFirstServer::PaquetFirstServer()
{
  _parsed = 0;
  _reponse = 0;
}

PaquetFirstServer::PaquetFirstServer(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetFirstServer::~PaquetFirstServer()
{
}

void		PaquetFirstServer::setReponse(uint8_t reponse)
{
  _reponse = reponse;
  _parsed = 0;
}

void		PaquetFirstServer::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_reponse);
}

void		PaquetFirstServer::parsePaquetFirstServer()
{
  size_t	ptr = 0;

  _reponse = readData<uint8_t>(ptr);
  _parsed = 1;
}

uint8_t		PaquetFirstServer::getReponse()
{
  if (!_parsed) {
    parsePaquetFirstServer();
  }
  return (_reponse);
}

void		PaquetFirstServer::dumpPaquet()
{
  if (!_parsed) {
    parsePaquetFirstServer();
  }
  std::cout << "PaquetFirstServer = { reponse : " << (int)_reponse << " };" << std::endl;
}
