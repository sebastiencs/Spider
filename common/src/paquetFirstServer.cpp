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
  this->setData(0, (void *)data, size);
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
  this->setData(0, &_reponse, 1);
}

void		PaquetFirstServer::parsePaquetFirstServer()
{
  char		*data;

  data = this->getData();
  memcpy(&_reponse, data, 1);
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
