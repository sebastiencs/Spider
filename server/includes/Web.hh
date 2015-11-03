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
# include <set>
# include "Spider.hh"
# include "SslContext.hh"
# include "Acceptor.hh"
# include "debug.hh"

class				Web
{
private:
  std::shared_ptr<SslContext>		_ctx;
  std::shared_ptr<Acceptor>		_acceptor;
  std::set<boost::shared_ptr<Spider>>	_spiders;

  void				insertSpider(const boost::shared_ptr<Spider> &);

public:
  Web(uint16_t);
  virtual ~Web();

  void				start();
  void				stop();
  void				waitSpider();
  void				deleteSpider(const boost::shared_ptr<Spider> &);
  boost::asio::io_service	&get_ioservice();
  void				sendCommand(boost::weak_ptr<PaquetCommandServer> paquet);
};

#endif /* !WEB_H_ */
