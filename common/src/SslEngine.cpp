//
// SslEngine.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Oct 20 14:39:18 2015 chapui_s
// Last update Tue Oct 20 14:39:18 2015 chapui_s
//

#include "SslEngine.hh"

SslEngine::SslEngine(boost::asio::io_service &ios, boost::asio::ssl::context &ctx)
  : _socket(ios, ctx)
{
  _error = false;
}

SslEngine::~SslEngine()
{
}

bool	SslEngine::isConnected() const
{
  return (!_error);
}

SslSocket::lowest_layer_type	&SslEngine::getSocket()
{
  return (_socket.lowest_layer());
}

void	SslEngine::doHandshake(boost::asio::ssl::stream_base::handshake_type type,
			       const std::function<void()> &func)
{
  _socket.async_handshake(type,
			  boost::bind(&SslEngine::checkHandshake,
			  	      this,
				      boost::asio::placeholders::error,
			  	      func));
}

void	SslEngine::async_read(void *buffer, size_t len, const std::function<void()> &func)
{
  boost::asio::async_read(_socket,
			  boost::asio::buffer(buffer, len),
			  boost::bind(&SslEngine::checkRead,
			  	      this,
				      boost::asio::placeholders::error,
			  	      func));
}

void	SslEngine::async_write(void *buffer, size_t len, const std::function<void()> &func)
{
  boost::asio::async_write(_socket,
			   boost::asio::buffer(buffer, len),
			   boost::bind(&SslEngine::checkWrite,
				       this,
				       boost::asio::placeholders::error,
				       func));
}

void	SslEngine::async_read_some(void *buffer, size_t len, const std::function<void()> &func)
{
  _socket.async_read_some(boost::asio::buffer(buffer, len),
			  boost::bind(&SslEngine::checkReadSome,
			  	      this,
				      boost::asio::placeholders::error,
			  	      func));
}

void	SslEngine::async_write_some(void *buffer, size_t len, const std::function<void()> &func)
{
  _socket.async_write_some(boost::asio::buffer(buffer, len),
			   boost::bind(&SslEngine::checkWriteSome,
				       this,
				       boost::asio::placeholders::error,
				       func));
}

void	SslEngine::checkHandshake(const boost::system::error_code &e, const std::function<void()> &f)
{
  if (e) {
    std::cerr << "SSL - Can't do handshake: " << e.message() << std::endl;
    _error = true;
  }
  else if (f) {
    _error = false;
    f();
  }
}

void	SslEngine::checkRead(const boost::system::error_code &e, const std::function<void()> &f)
{
  if (e) {
    std::cerr << "SSL - Can't read: " << e.message() << std::endl;
    _error = true;
  }
  else if (f) {
    f();
  }
}

void	SslEngine::checkWrite(const boost::system::error_code &e, const std::function<void()> &f)
{
  if (e) {
    std::cerr << "SSL - Can't write: " << e.message() << std::endl;
    _error = true;
  }
  else if (f) {
    f();
  }
}

void	SslEngine::checkReadSome(const boost::system::error_code &e, const std::function<void()> &f)
{
  if (e) {
    std::cerr << "SSL - Can't read some: " << e.message() << std::endl;
    _error = true;
  }
  else if (f) {
    f();
  }
}
void	SslEngine::checkWriteSome(const boost::system::error_code &e, const std::function<void()> &f)
{
  if (e) {
    std::cerr << "SSL - Can't write some: " << e.message() << std::endl;
    _error = true;
  }
  else if (f) {
    f();
  }
}
