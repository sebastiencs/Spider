//
// Web.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:06:00 2015 chapui_s
// Last update Wed Oct 21 09:06:00 2015 chapui_s
//

#ifndef WEB_H_
# define WEB_H_

# include <iostream>
# include <boost/cstdint.hpp>
# include "SslContext.hh"
# include "debug.hh"

class				Web
{
private:
  std::unique_ptr<SslContext>	_ctx;

public:
  Web(const std::string &, uint16_t);
  virtual ~Web();

  void				start();
  void				stop();
};

#endif /* !WEB_H_ */
