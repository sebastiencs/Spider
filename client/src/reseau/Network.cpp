#include <iostream>
#include "reseau/Network.hh"
#include "paquetFirstClient.hh"

#ifndef CERTIFICATE_FILE
# define CERTIFICATE_FILE ("client.crt")
#endif

Network::Network(const std::string& port, const std::string& ip) :
	_port(port), _ip(ip), _ctx(boost::asio::ssl::context::sslv23)
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
	_isConnected = 0;
	boost::asio::ip::tcp::endpoint endpoint = *_iterator;
	_engine->getSocket().async_connect(endpoint, [this](const boost::system::error_code& e)
	{
		_engine->doHandshake(boost::asio::ssl::stream_base::client, [this]()
		{
			_isConnected = 1;
		});
	});
	_ios.run();
}

void Network::write(void* data, size_t size) {
	_engine->async_write(data, size, []() {});
}


void Network::writePaquet(const Paquet& paquet){
	_engine->writePaquet(paquet, []() {});
}