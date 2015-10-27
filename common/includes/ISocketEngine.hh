//
// ISocketEngine.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Tue Oct 20 14:04:40 2015 chapui_s
// Last update Tue Oct 20 14:04:40 2015 chapui_s
//

#ifndef ISOCKETENGINE_H_
# define ISOCKETENGINE_H_

# include <boost/asio/ssl.hpp>
# include <boost/bind.hpp>
# include <boost/asio.hpp>
# include <iostream>
# include "paquet.hh"

typedef boost::asio::ssl::stream<boost::asio::ip::tcp::socket> SslSocket;

class		ISocketEngine
{
public:
  virtual ~ISocketEngine() {};

  virtual SslSocket::lowest_layer_type	&getSocket() = 0;
  virtual void				doHandshake(boost::asio::ssl::stream_base::handshake_type,
						    const std::function<void()> &) = 0;
  virtual void				async_read(void *, size_t, const std::function<void()> &) = 0;
  virtual void				async_write(void *, size_t, const std::function<void()> &) = 0;
  virtual void				async_read_some(void *, size_t, const std::function<void()> &) = 0;
  virtual void				async_write_some(void *, size_t, const std::function<void()> &) = 0;
  virtual void				handleError(const std::function<void()> &) = 0;
  virtual void			writePaquet(const Paquet &, const std::function<void()> &) = 0;
};

#endif /* !ISOCKETENGINE_H_ */
