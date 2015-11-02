#include <iostream>
#include <boost/thread.hpp>
#include "reseau/Network.hh"
#include "paquetFirstClient.hh"

#ifndef CERTIFICATE_FILE
# define CERTIFICATE_FILE ("client.crt")
#endif

Network::Network(const std::string& port, const std::string& ip, Packager* packager) :
	_port(port), _ip(ip), _ctx(boost::asio::ssl::context::sslv23), _packager(packager)
{
	boost::asio::ip::tcp::resolver resolver(_ios);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	_iterator = resolver.resolve(query);

	_ctx.load_verify_file(CERTIFICATE_FILE);
	_ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
	_engine = new SslEngine(_ios, _ctx);
}


Network::~Network() {
}

void Network::initNetwork() {
	boost::asio::spawn(_ios, [this](boost::asio::yield_context yield) {
		boost::asio::ip::tcp::endpoint endpoint = *_iterator;
		boost::system::error_code ec;

	    for (;;) {
	      _engine->getSocket().async_connect(endpoint, yield[ec]);
		  if (!ec) {
			  std::cout << "SSL: initializing HandShake" << std::endl;
			  _engine->doHandshake(boost::asio::ssl::stream_base::client, yield);
			  if (!ec) {
				  sendFirstPaquet();
			  }
		  }
		  boost::chrono::nanoseconds(2000);
		}
	  });
	_ios.run();
}


// void Network::initNetwork() {
//   boost::asio::ip::tcp::endpoint endpoint = *_iterator;
//   _engine->getSocket().async_connect(endpoint, [this](const boost::system::error_code& e)
// 				     {
// 				       if (!e) {
// 					 std::cout << "SSL: initializing HandShake" << std::endl;
// 					 _engine->doHandshake(boost::asio::ssl::stream_base::client, [this]() { sendFirstPaquet(); });
// 				       }
// 				       else {
// 					 _engine->getSocket().close();
// 					 std::cerr << "SSL: Connect failed: " << e << std::endl;
// 				       }
// 				     });
//   _ios.run();
// }


void Network::sendFirstPaquet()
{
	PaquetFirstClient	paquet;

	paquet.setVersion(1);
	char hostName[128];
	gethostname(hostName, sizeof(hostName));
	paquet.setName(hostName);
	paquet.createPaquet();

	_engine->writePaquet(paquet, [this]() {
		char ret;
		_engine->async_read(&ret, 1, [this, &ret]() {
			std::cout << "SSL: server RET value " << (int)ret << std::endl;
			if (ret)
				boost::asio::spawn(_ios, [this](boost::asio::yield_context yield) {networkLoop(yield); });
			else
			{
				_engine->getSocket().close();
				std::cerr << "SSl: Error: Wrong protocol version" << std::endl;
			}
		});
	});
}

void Network::networkLoop(boost::asio::yield_context yield)
{
	while (1) {
		while (_packager->isLeft() == 0)
		{
			std::cout << "Waiting packager" << std::endl;
			boost::this_thread::sleep_for(boost::chrono::nanoseconds(2000));
		}

		Paquet *paquet = _packager->getPaquet();
		std::cout << "SENDING PAQUET: " << *paquet << std::endl;
		if (_engine->writePaquet(*paquet, yield) == -1) {
			return;
		}
		_packager->supprPaquet();
	}
}
