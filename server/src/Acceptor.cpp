//
// Acceptor.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 22 15:10:41 2015 chapui_s
// Last update Thu Oct 22 15:10:41 2015 chapui_s
//

#include "Acceptor.hh"

Acceptor::Acceptor(SslContext &ctx, uint16_t port)
  :  _acceptor(_ios, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
     _ctx(ctx)
{
  DEBUG_MSG("Acceptor created");
}

Acceptor::~Acceptor()
{
  DEBUG_MSG("Acceptor destroyed");
}

void	Acceptor::async_accept(std::function<void(boost::shared_ptr<ISocketEngine> &)> &f)
{
  boost::shared_ptr<ISocketEngine>	socket(new SslEngine(_ios, _ctx.getCtx()));

  _acceptor.async_accept(socket->getSocket(),
  			 boost::bind(&Acceptor::handleAccept, this,
				     socket,
				     f,
  			 	     boost::asio::placeholders::error));
}

void	Acceptor::handleAccept(boost::shared_ptr<ISocketEngine> &sock,
			       std::function<void(boost::shared_ptr<ISocketEngine> &)> &f,
			       const boost::system::error_code &e)
{
  if (e) {
    std::cerr << "error handleAccept" << std::endl;
  }
  else {
    f(sock);
  }
  async_accept(f);
}

void	Acceptor::start()
{
 _ios.run();
}

void	Acceptor::stop()
{
  _ios.stop();
}
