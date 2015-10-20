//
// paquetCommandClient.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 13:02:05 2015 chapui_s
// Last update Thu Oct 15 13:02:05 2015 chapui_s
//

#include "paquetCommandClient.hh"

PaquetCommandClient::PaquetCommandClient()
{
  _id = PaquetCommandClient::ID;
  _parsed = 0;
  _ok = 0;
  _sizeData = 0;
  _dataReponse = 0;
}

PaquetCommandClient::PaquetCommandClient(const void *data, size_t size)
{
  size_t	ptr = 0;

  writeData<char>(ptr, reinterpret_cast<const char *>(data), size);
  _parsed = 0;
}

PaquetCommandClient::~PaquetCommandClient()
{
  delete[] _dataReponse;
}

void		PaquetCommandClient::setOk(uint16_t ok)
{
  _ok = ok;
  _parsed = 0;
}

void		PaquetCommandClient::setDataReponse(const std::string &reponse)
{
  _sizeData = reponse.size();
  _dataReponse = new char[_sizeData + 1]();
  std::copy(reponse.data(), reponse.data() + _sizeData, _dataReponse);
  _parsed = 0;
}

void		PaquetCommandClient::createPaquet()
{
  size_t	ptr = 0;

  writeData<uint8_t>(ptr, &_id);
  writeData<uint8_t>(ptr, &_ok);
  writeData<uint16_t>(ptr, &_sizeData);
  writeData<char>(ptr, _dataReponse, _sizeData);
}

void		PaquetCommandClient::parsePaquetCommandClient()
{
  size_t	ptr = 0;

  _id = readData<uint8_t>(ptr);
  _ok = readData<uint8_t>(ptr);
  _sizeData = readData<uint16_t>(ptr);
  if (_sizeData) {
    delete[] _dataReponse;
    _dataReponse = new char[_sizeData + 1]();
    readData<char>(ptr, _dataReponse, _sizeData);
  }
  _parsed = 1;
}

uint8_t		PaquetCommandClient::getOk()
{
  if (!_parsed) {
    parsePaquetCommandClient();
  }
  return (_ok);
}

char		*PaquetCommandClient::getDataReponse()
{
  if (!_parsed) {
    parsePaquetCommandClient();
  }
  return (_dataReponse);
}

void		PaquetCommandClient::dumpPaquet()
{
  std::cout << *this;
}

std::ostream	&operator<<(std::ostream &os, PaquetCommandClient &p)
{
  int		ok = p.getOk();
  std::string	reponse = p.getDataReponse();

  os << "PaquetCommandClient = { ok ? : " << ok;
  os << ", SizeData : " << reponse.size();
  if (reponse.size())
    os << ", DataReponse : '" << reponse << "'";
  os << " };" << std::endl;
  return (os);
}
