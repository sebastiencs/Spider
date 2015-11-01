//
// SslEngine.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Oct 20 14:39:18 2015 chapui_s
// Last update Tue Oct 20 14:39:18 2015 chapui_s
//

#include "debug.hh"
#include "SslEngine.hh"

#ifdef __GNUC__
# define UNUSED __attribute__((__unused__))
#else // !__GNUC__
# define UNUSED
#endif // !__GNUC__

SslEngine::SslEngine(boost::asio::io_service &ios, boost::asio::ssl::context &ctx)
  : _socket(ios, ctx)
{
  DEBUG_MSG("SSlEngine created");
}

SslEngine::~SslEngine()
{
  DEBUG_MSG("SSlEngine deleted");
}

SslSocket::lowest_layer_type	&SslEngine::getSocket()
{
  return (_socket.lowest_layer());
}

void	SslEngine::doHandshake(boost::asio::ssl::stream_base::handshake_type type,
			       const std::function<void()> &func)
{
  _socket.async_handshake(type, [this, func](const boost::system::error_code &e) {
      if (e) {
	std::cerr << "SSL - Can't do handshake: " << e.message() << std::endl;
	_errorFunc();
      }
      else {
	func();
      }
    });
}

void	SslEngine::async_read(void *buffer, size_t len, const std::function<void()> &func)
{
  boost::asio::async_read(_socket, boost::asio::buffer(buffer, len),
    [this, func](const boost::system::error_code &e, std::size_t bytes_transferred UNUSED ) {
      if (e) {
	std::cerr << "SSL - Can't read: " << e.message() << std::endl;
	_errorFunc();
      }
      else {
	func();
      }
    });
}

void    SslEngine::async_write(void *buffer, size_t len, const std::function<void()> &func)
{
	boost::asio::async_write(_socket, boost::asio::buffer(buffer, len),
		[this, func](const boost::system::error_code &e, std::size_t bytes_transferred) {
		if (e) {
			std::cerr << "SSL - Can't write: " << e.message() << std::endl;
			_errorFunc();
		}
		else {
			std::cout << "Envoyé: " << (int)bytes_transferred << std::endl;
			func();
		}
	});
}

void	SslEngine::async_read_some(void *buffer, size_t len, const std::function<void()> &func)
{
  _socket.async_read_some(boost::asio::buffer(buffer, len),
    [this, func](const boost::system::error_code &e, std::size_t bytes_transferred UNUSED ) {
      if (e) {
	std::cerr << "SSL - Can't read some: " << e.message() << std::endl;
	_errorFunc();
      }
      else {
	func();
      }
    });
}

void	SslEngine::async_write_some(void *buffer, size_t len, const std::function<void()> &func)
{
  _socket.async_write_some(boost::asio::buffer(buffer, len),
    [this, func](const boost::system::error_code &e, std::size_t bytes_transferred UNUSED ) {
      if (e) {
	std::cerr << "SSL - Can't write some: " << e.message() << std::endl;
	_errorFunc();
      }
      else {
	func();
      }
    });
}

void    SslEngine::writePaquet(const Paquet &paquet, const std::function<void()> &func)
{
#ifdef DEBUG
	if (!paquet.getSize()) {
		DEBUG_MSG("Trying to send empty paquet");
	}
#endif // !DEBUG                                                                                                                                                                                                                               
	std::cout << "WRITEPAQUET: " << paquet << std::endl;
	std::cout << "WRITEPAQUET SIZE: " << paquet.getSize() << std::endl;
	async_write(paquet.getData(), paquet.getSize(), func);
}

void	SslEngine::handleError(const std::function<void()> &f)
{
  _errorFunc = f;
}
