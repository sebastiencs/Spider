//
// paquet.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 15 07:47:20 2015 chapui_s
// Last update Thu Oct 15 07:47:20 2015 chapui_s
//

#ifndef PAQUET_H_
# define PAQUET_H_

# include <boost/cstdint.hpp>
# include <iostream>
# include <type_traits>

class		Paquet
{
protected:

  enum { LENGTH_PAQUET = 1 };

  char		*_data;
  size_t	_size;

  void	setSize(size_t);

public:
  Paquet();
  virtual ~Paquet();

  size_t	getSize() const;

  void		changeSize(size_t);

  void	dumpPaquetHexa() const;
  virtual void	dumpPaquet() = 0;

  template<typename T>
  void		writeData(size_t &ptr, const T *new_data, size_t len = 0) {
    size_t	i = 0;

    if (!len && !std::is_same<T, char>::value) {
      len = sizeof(T);
    }
    if (ptr + len >= _size) {
      changeSize(ptr + len);
    }
    for (i = 0; i < len; i += 1) {
      _data[ptr + i] = reinterpret_cast<const uint8_t *>(new_data)[i];
    }
    ptr += i;
  }

  template<typename T>
  T		readData(size_t &ptr, T *buffer = 0, size_t len = 0) const {
    T		value = 0;
    uint8_t	*byte;

    if (!len && !std::is_same<T, char>::value) {
      len = sizeof(T);
    }

    byte = reinterpret_cast<uint8_t *>((buffer) ? (buffer) : (&value));

    if (ptr + len <= _size) {
      for (size_t i = 0; i < len; i += 1) {
	byte[i] = _data[ptr];
	ptr += 1;
      }
    }
    return (value);
  }
};

#endif /* !PAQUET_H_ */
