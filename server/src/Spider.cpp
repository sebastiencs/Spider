//
// Spider.cpp<travaux> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:18:47 2015 chapui_s
// Last update Wed Oct 21 09:18:47 2015 chapui_s
//

#include "Spider.hh"
#include "Web.hh"

Spider::Spider(const boost::shared_ptr<ISocketEngine> &socket, Web &web)
  : _socket(socket),
    _web(web)
{
  DEBUG_MSG("Spider created");
  _socket->handleError([this](){dieInDignity();});
}

Spider::~Spider()
{
  DEBUG_MSG("Spider deleted");
}

void		Spider::dieInDignity()
{
  _web.deleteSpider(shared_from_this());
}

void	Spider::finish()
{
  std::cout << "BUFFER: " << _buffer << std::endl;
}

void		Spider::prepareFirstConnection()
{
  _socket->doHandshake(boost::asio::ssl::stream_base::server, [this](){doFirstConnection();});
}

void			Spider::doFirstConnection()
{
  PaquetFirstClient	paquet;

  _socket->async_read(_buffer.data(), 4, [this, &paquet]() {
      uint16_t		sizeName;

      paquet.setVersion(_buffer.getValue<uint16_t>());
      sizeName = _buffer.getValue<uint16_t>();

      _socket->async_read(_buffer.data(), sizeName, [this, &paquet, sizeName]() {
      	  _buffer.getValue<char>(_str, sizeName);
      	  paquet.setName(_str);
      	});

      // std::cout << "BUFFER: " << _buffer << std::endl;
    });
}
