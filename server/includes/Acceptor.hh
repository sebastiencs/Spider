//
// Acceptor.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 22 14:13:49 2015 chapui_s
// Last update Thu Oct 22 14:13:49 2015 chapui_s
//

#ifndef ACCEPTOR_H_
# define ACCEPTOR_H_

# include <boost/asio/ssl.hpp>
# include <boost/asio.hpp>
# include "SslContext.hh"
# include "SslEngine.hh"
# include "debug.hh"

class			Acceptor
{
private:
  std::unique_ptr<boost::asio::io_service>	_ios;
  boost::asio::ip::tcp::acceptor		_acceptor;
  SslContext					&_ctx;

public:
  Acceptor(SslContext &, uint16_t);
  virtual ~Acceptor();

  void			async_accept(std::function<void(boost::shared_ptr<ISocketEngine> &)> &);
  void			handleAccept(boost::shared_ptr<ISocketEngine> &,
				     std::function<void(boost::shared_ptr<ISocketEngine> &)> &,
				     const boost::system::error_code &);
  void			start();
  void			stop();
};

#endif /* !ACCEPTOR_H_ */