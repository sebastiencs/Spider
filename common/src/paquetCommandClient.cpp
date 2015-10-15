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
  this->setData(0, (void *)data, size);
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
  memcpy(_dataReponse, reponse.data(), _sizeData);
  _parsed = 0;
}

void		PaquetCommandClient::createPaquet()
{
  size_t	ptr;

  ptr = 0;
  this->setData(ptr, &_id, 1);
  ptr += 1;
  this->setData(ptr, &_ok, 1);
  ptr += 1;
  this->setData(ptr, &_sizeData, 2);
  ptr += 2;
  if (_sizeData) {
    this->setData(ptr, _dataReponse, _sizeData);
  }
}

void		PaquetCommandClient::parsePaquetCommandClient()
{
  char		*data;
  size_t	ptr;

  data = this->getData();
  ptr = 0;
  memcpy(&_id, data + ptr, 1);
  ptr = 1;
  memcpy(&_ok, data + ptr, 1);
  ptr = 1;
  memcpy(&_sizeData, data + ptr, 2);
  ptr += 2;
  if (_sizeData) {
    delete[] _dataReponse;
    _dataReponse = new char[_sizeData + 1]();
    memcpy(_dataReponse, data + ptr, _sizeData);
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
  if (!_parsed) {
    parsePaquetCommandClient();
  }
  std::cout << "PaquetCommandClient = { ok ? : " << _ok;
  std::cout << ", SizeData : " << _sizeData;
  if (_sizeData)
    std::cout << ", DataReponse : '" << _dataReponse << "'";
  std::cout << " };" << std::endl;
}
