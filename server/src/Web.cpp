//
// Web.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:14:05 2015 chapui_s
// Last update Wed Oct 21 09:14:05 2015 chapui_s
//

#include "Spider.hh"
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
  _acceptor->async_accept([this](boost::shared_ptr<ISocketEngine> &sock) {
      const boost::shared_ptr<Spider>	spider(new Spider(sock, *this));

      insertSpider(spider);
      spider->prepareFirstConnection();
    });
}

void		Web::insertSpider(const boost::shared_ptr<Spider> &spider)
{
  _spiders.insert(spider);
}

void		Web::deleteSpider(const boost::shared_ptr<Spider> &spider)
{
  _spiders.erase(spider);
}

boost::asio::io_service	&Web::get_ioservice()
{
  return (_acceptor->get_ioservice());
}
