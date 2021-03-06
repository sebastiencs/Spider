//
// paquet.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 08:09:15 2015 chapui_s
// Last update Tue Oct 27 12:21:08 2015 bresci_b bresci_b
//

#include <iostream>
#include "paquet.hh"

Paquet::Paquet()
{
  _data = new char[Paquet::LENGTH_PAQUET]();
  _size = Paquet::LENGTH_PAQUET;
}

Paquet::~Paquet()
{
  if (_data)
    delete[] _data;
}

void	Paquet::setSize(size_t new_size)
{
  _size = new_size;
}

size_t	Paquet::getSize() const {
  return (_size);
}

char	*Paquet::getData() const {
  return (_data);
}

void	Paquet::changeSize(size_t size) {
  char	*tmp = new char[size];

  std::copy(_data, _data + _size, tmp);
  delete[] _data;
  _data = tmp;
  _size = size;
}

void	Paquet::dumpPaquetHexa() const
{
  std::cout << "Paquet = { ";
  std::cout << std::hex << std::uppercase;
  for (size_t i = 0; i < _size; i += 1) {
    std::cout << (int)((unsigned char)_data[i]) << " ";
  }
  std::cout << std::dec << "}; " << std::endl;
}

std::ostream	&operator<<(std::ostream &os, const Paquet &p)
{
  char		*data;

  data = p.getData();
  os << "Paquet = { ";
  os << std::hex << std::uppercase;
  for (size_t i = 0; i < p.getSize(); i += 1) {
    os << (int)((unsigned char)data[i]) << " ";
  }
  os << std::dec << "}; " << std::endl;
  return (os);
}
