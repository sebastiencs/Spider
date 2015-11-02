//
// SslContext.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 22 12:05:13 2015 chapui_s
// Last update Thu Oct 22 12:05:13 2015 chapui_s
//

#include <iostream>
#include "debug.hh"
#include "SslContext.hh"

#ifndef CERTIFICATE_FILE
# define CERTIFICATE_FILE ("server.crt")
#endif

#ifndef PRIVATE_KEY_FILE
# define PRIVATE_KEY_FILE ("server.key")
#endif

#ifndef DH_FILE
# define DH_FILE ("dh1024.pem")
#endif

SslContext::SslContext()
  : _ctx(boost::asio::ssl::context::sslv23)
{
  DEBUG_MSG("Setting SslContext");
  _ctx.set_options(boost::asio::ssl::context::default_workarounds
		    | boost::asio::ssl::context::no_sslv2
		    | boost::asio::ssl::context::single_dh_use);
  _ctx.use_certificate_chain_file(CERTIFICATE_FILE);
  _ctx.use_private_key_file(PRIVATE_KEY_FILE, boost::asio::ssl::context::pem);
  _ctx.use_tmp_dh_file(DH_FILE);
}

SslContext::~SslContext()
{
  DEBUG_MSG("SslContext Closed");
}

boost::asio::ssl::context	&SslContext::getCtx()
{
  return (_ctx);
}
