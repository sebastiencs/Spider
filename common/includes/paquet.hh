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

# include <unistd.h>
# include <stdint.h>

class		Paquet
{
protected:

  enum { LENGTH_PAQUET = 10 };

  char		*_data;
  size_t	_size;

  void	setSize(size_t);

public:
  Paquet();
  virtual ~Paquet();

  char	*getData() const;
  void	setData(size_t, void *, size_t);

  void	dumpPaquetHexa() const;
  virtual void	dumpPaquet() = 0;
};

#endif /* !PAQUET_H_ */
