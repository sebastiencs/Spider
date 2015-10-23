//
// Buffer.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Oct 23 16:42:10 2015 chapui_s
// Last update Fri Oct 23 16:42:10 2015 chapui_s
//

#include "Buffer.hh"

Buffer::Buffer()
  : _buffer(Buffer::BUFFER_SIZE),
    _ptr(0)
{
}

Buffer::~Buffer()
{
}

void		*Buffer::data() const
{
  return ((uint8_t *)_buffer.data());
}

std::ostream		&operator<<(std::ostream &os, const Buffer &buffer)
{
  char			*data;

  data = (char *)buffer.data();
  for (size_t i = 0; i < Buffer::BUFFER_SIZE; i += 1) {
    os << (char)data[i];
  }
  return (os);
}
