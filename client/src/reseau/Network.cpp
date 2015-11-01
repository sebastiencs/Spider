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
	boost::asio::ip::tcp::endpoint endpoint = *_iterator;
	_engine->getSocket().async_connect(endpoint, [this](const boost::system::error_code& e)
	{
		if (!e)
			_engine->doHandshake(boost::asio::ssl::stream_base::client, [this]() { sendFirstPaquet(); });
		else {
			_engine->getSocket().close();
			std::cerr << "Connect failed: " << e << std::endl;
		}
	});
	_ios.run();
}

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
			if (ret)
				networkLoop();
			else
			{
				_engine->getSocket().close();
				std::cerr << "Error: Wrong protocol version" << std::endl;
			}
		});
	});
}

void Network::networkLoop()
{
	while (1) {
		if (_packager->isLeft() > 0) {
			Paquet *paquet = _packager->getPaquet();
			_engine->writePaquet(*paquet, []() {});
		}
		boost::this_thread::sleep_for(boost::chrono::nanoseconds(500));
	}
}
