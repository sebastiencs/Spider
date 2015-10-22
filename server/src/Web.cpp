//
// Web.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:14:05 2015 chapui_s
// Last update Wed Oct 21 09:14:05 2015 chapui_s
//

#include "Web.hh"

Web::Web(const std::string &addr, uint16_t port)
  : _ctx(new SslContext())
{
  DEBUG_MSG("Web is running");
}

Web::~Web()
{
  DEBUG_MSG("Closing Web");
}

void		Web::start()
{
}

void		Web::stop()
{
}
