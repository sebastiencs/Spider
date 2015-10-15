//
// paquetCommands.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 12:48:10 2015 chapui_s
// Last update Thu Oct 15 12:48:10 2015 chapui_s
//

#include "paquetCommandServer.hh"

PaquetCommandServer::PaquetCommandServer()
{
  _id = PaquetCommandServer::ID;
  _parsed = 0;
  _sizeCommand = 0;
  _command = 0;
}

PaquetCommandServer::PaquetCommandServer(const void *data, size_t size)
{
  this->setData(0, (void *)data, size);
  _parsed = 0;
}

PaquetCommandServer::~PaquetCommandServer()
{
  delete[] _command;
}

void		PaquetCommandServer::setCommand(const std::string &command)
{
  _sizeCommand = command.size();
  _command = new char[_sizeCommand + 1]();
  memcpy(_command, command.data(), _sizeCommand);
  _parsed = 0;
}

void		PaquetCommandServer::createPaquet()
{
  size_t	ptr;

  ptr = 0;
  this->setData(ptr, &_id, 1);
  ptr += 1;
  this->setData(ptr, &_sizeCommand, 2);
  ptr += 2;
  if (_sizeCommand) {
    this->setData(ptr, _command, _sizeCommand);
  }
}

void		PaquetCommandServer::parsePaquetCommandServer()
{
  char		*data;
  size_t	ptr;

  data = this->getData();
  ptr = 0;
  memcpy(&_id, data + ptr, 1);
  ptr = 1;
  memcpy(&_sizeCommand, data + ptr, 2);
  ptr += 2;
  if (_sizeCommand) {
    delete[] _command;
    _command = new char[_sizeCommand + 1]();
    memcpy(_command, data + ptr, _sizeCommand);
  }
  _parsed = 1;
}

char		*PaquetCommandServer::getCommand()
{
  if (!_parsed) {
    parsePaquetCommandServer();
  }
  return (_command);
}

void		PaquetCommandServer::dumpPaquet()
{
  if (!_parsed) {
    parsePaquetCommandServer();
  }
  std::cout << "PaquetCommandServer = { sizeCommand : " << _sizeCommand;
  if (_sizeCommand)
    std::cout << ", command : '" << _command << "'";
  std::cout << " };" << std::endl;
}
