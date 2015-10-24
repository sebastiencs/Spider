//
// SslContext.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 22 12:02:47 2015 chapui_s
// Last update Thu Oct 22 12:02:47 2015 chapui_s
//

#ifndef SSLCONTEXT_H_
# define SSLCONTEXT_H_

# include <boost/asio/ssl.hpp>

class		SslContext
{
private:
  boost::asio::ssl::context _ctx;

public:
  SslContext();
  virtual ~SslContext();

  boost::asio::ssl::context	&getCtx();
};

#endif /* !SSLCONTEXT_H_ */
