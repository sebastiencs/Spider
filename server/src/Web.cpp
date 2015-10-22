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

Web::Web(uint16_t port)
  : _ctx(new SslContext()),
    _acceptor(new Acceptor(*_ctx, port))
{
  DEBUG_MSG("Web is running");
  waitSpider();
}

Web::~Web()
{
  DEBUG_MSG("Closing Web");
}

void		Web::start()
{
  _acceptor->start();
}

void		Web::stop()
{
  _acceptor->stop();
}

void		Web::waitSpider()
{
  std::function<void(boost::shared_ptr<ISocketEngine> &)> f = boost::bind(&Web::handleNewSpider, this, _1);

  _acceptor->async_accept(f);
}

void		Web::handleNewSpider(boost::shared_ptr<ISocketEngine> &sock)
{
  std::cout << "New Spider !" << std::endl;
}
