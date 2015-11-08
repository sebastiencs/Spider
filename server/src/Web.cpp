//
// Web.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:14:05 2015 chapui_s
// Last update Wed Oct 21 09:14:05 2015 chapui_s
//

#include <boost/range/algorithm/find.hpp>
#include "Spider.hh"
#include "Web.hh"

Web::Web(uint16_t port, std::list<boost::shared_ptr<IPlugin>> &listPlugins)
  : _ctx(new SslContext()),
    _acceptor(new Acceptor(*_ctx, port)),
    _listPlugins(listPlugins)
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
      const boost::shared_ptr<Spider>	spider(new Spider(sock, *this, _listPlugins));

      insertSpider(spider);
      spider->prepareFirstConnection();
    });
}

int		Web::listSpider()
{
  if (_spiders.size()) {

    int		num = 0;

    std::cout << "Listing Spiders:" << std::endl;
    for (auto &spider : _spiders) {
      std::cout << num << " - " << spider->getName() << std::endl;
      num += 1;
    }
  }
  else {
    std::cout << "No spiders connected" << std::endl;
  }
  return (0);
}

void		Web::sendCommand(boost::weak_ptr<PaquetCommandServer> p)
{
  boost::shared_ptr<PaquetCommandServer>	paquet = p.lock();

  if (!_spiders.size()) {
    std::cout << "No spiders connected" << std::endl;
  }
  else {
    for (auto &spider : _spiders) {
      spider->getSocket()->writePaquet(*paquet, [this]() {
#ifdef DEBUG
	  std::cout << "Command sent" << std::endl;
#endif // !DEBUG
	});
    }
  }
}

void		Web::sendCommand(boost::weak_ptr<PaquetCommandServer> p, std::list<std::string> listSpider)
{
  boost::shared_ptr<PaquetCommandServer>	paquet = p.lock();

  for (auto &spider : _spiders) {
    if (std::find(listSpider.begin(), listSpider.end(), spider->getName()) != listSpider.end()) {
      spider->getSocket()->writePaquet(*paquet, [this, &spider]() {
#ifdef DEBUG
	  std::cout << "Command sent to " << spider->getName() << std::endl;
#endif // !DEBUG
	});
    }
  }
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
