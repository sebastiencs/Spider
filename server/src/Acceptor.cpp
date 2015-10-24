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

void	Acceptor::async_accept(const std::function<void(boost::shared_ptr<ISocketEngine> &)> &func)
{
  boost::shared_ptr<ISocketEngine>	socket(new SslEngine(_ios, _ctx.getCtx()));

  _acceptor.async_accept(socket->getSocket(),
    [this, socket, func](const boost::system::error_code &e) mutable {
      if (e) {
  	std::cerr << "error handleAccept: " << e.message() << std::endl;
      }
      else {
  	func(socket);
      }
      async_accept(func);
    });
}

void	Acceptor::start()
{
 _ios.run();
}

void	Acceptor::stop()
{
  _ios.stop();
}
