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
  _sizeCommand = 0;
  _command = 0;
}

PaquetCommandServer::PaquetCommandServer(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetCommandServer::~PaquetCommandServer()
{
  if (_command)
    delete[] _command;
}

void		PaquetCommandServer::setCommand(const std::string &command)
{
  _sizeCommand = command.size();
  _command = new char[_sizeCommand + 1]();
  std::copy(command.data(), command.data() + _sizeCommand, _command);
  _parsed = 0;
}

void		PaquetCommandServer::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint16_t>(ptr, &_sizeCommand);
  writeData<char>(ptr, _command, _sizeCommand);
}

void		PaquetCommandServer::parsePaquetCommandServer()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _sizeCommand = readData<uint16_t>(ptr);
  if (_sizeCommand) {
    delete[] _command;
    _command = new char[_sizeCommand + 1]();
    readData<char>(ptr, _command, _sizeCommand);
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
  std::cout << *this;
}

std::ostream	&operator<<(std::ostream &os, PaquetCommandServer &p)
{
  std::string	command = p.getCommand();

  os << "PaquetCommandServer = { sizeCommand : " << command.size();
  if (command.size())
    os << ", command : '" << command << "'";
  os << " };" << std::endl;
  return (os);
}
