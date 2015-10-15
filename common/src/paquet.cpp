//
// paquet.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 08:09:15 2015 chapui_s
// Last update Thu Oct 15 08:09:15 2015 chapui_s
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
  delete[] _data;
}

char	*Paquet::getData() const
{
  return (_data);
}

void	Paquet::setData(size_t ptr, void *new_data, size_t length)
{
  if (ptr + length >= _size) {
    char *tmp = new char[ptr + length]();
    std::copy(_data, _data + _size, tmp);
    delete[] _data;
    _data = tmp;
    _size = ptr + length;
  }
  for (size_t i = 0; i < length; i += 1) {
    _data[ptr + i] = ((char *)(new_data))[i];
  }
}

void	Paquet::setSize(size_t new_size)
{
  _size = new_size;
}

size_t	Paquet::getSize() const {
  return (_size);
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
