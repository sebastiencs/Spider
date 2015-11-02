//
// SslEngine.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Oct 20 14:35:59 2015 chapui_s
// Last update Tue Oct 20 14:35:59 2015 chapui_s
//

#ifndef SSLENGINE_H_
# define SSLENGINE_H_

# include <boost/asio/spawn.hpp>
# include "ISocketEngine.hh"
# include "paquet.hh"

class		SslEngine : public ISocketEngine
{
private:
  SslSocket	_socket;

  std::function<void()>	_errorFunc = [](){};

public:
  SslEngine(boost::asio::io_service &, boost::asio::ssl::context &);
  virtual ~SslEngine();

  virtual SslSocket::lowest_layer_type	&getSocket();
  virtual void			doHandshake(boost::asio::ssl::stream_base::handshake_type,
					    const std::function<void()> &);
  virtual int			doHandshake(boost::asio::ssl::stream_base::handshake_type,
					    boost::asio::yield_context);
  virtual void			async_read(void *, size_t, const std::function<void()> &);
  virtual int			async_read(void *buffer, size_t len, boost::asio::yield_context yield);
  virtual int			async_write(void *buffer, size_t len, boost::asio::yield_context yield);
  virtual void			async_write(void *, size_t, const std::function<void()> &);
  virtual void			async_read_some(void *, size_t, const std::function<void()> &);
  virtual void			async_write_some(void *, size_t, const std::function<void()> &);
  virtual void			handleError(const std::function<void()> &);
  virtual void			writePaquet(const Paquet &, const std::function<void()> &);
  virtual int			writePaquet(const Paquet &paquet, boost::asio::yield_context yield);
};

#endif /* !SSLENGINE_H_ */
