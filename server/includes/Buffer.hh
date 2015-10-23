//
// Buffer.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Fri Oct 23 16:19:40 2015 chapui_s
// Last update Fri Oct 23 16:19:40 2015 chapui_s
//

#ifndef BUFFER_H_
# define BUFFER_H_

# include <vector>
# include <boost/cstdint.hpp>
# include <iostream>
# include "paquetCommandClient.hh"
# include "paquetCommandServer.hh"
# include "paquetFirstClient.hh"
# include "paquetFirstServer.hh"
# include "paquetMouse.hh"
# include "paquetKeys.hh"

class		Buffer
{
private:
  std::vector<uint8_t>	_buffer;
  size_t		_ptr;

public:

  enum { BUFFER_SIZE = 2048 };

  Buffer();
  virtual ~Buffer();

  void		*data() const;

  template<typename T>
  T		getValue(T *buffer = 0, size_t len = 0)
    {
      T		value = 0;
      uint8_t	*byte;

      if (!len && !std::is_same<T, char>::value) {
	len = sizeof(T);
      }

      byte = reinterpret_cast<uint8_t *>((buffer) ? (buffer) : (&value));

      if (_ptr + len <= _buffer.size()) {
	for (size_t i = 0; i < len; i += 1) {
	  byte[i] = _buffer.at(_ptr);
	  _ptr += 1;
	}
      }
      return (value);
    }
};

std::ostream		&operator<<(std::ostream &, const Buffer &);

#endif /* !BUFFER_H_ */
