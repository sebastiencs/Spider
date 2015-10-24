#include "reseau/Network.hh"

Network::Network(uint16_t port, const std::string& ip) :
	_port(port), _ip(ip), _ctx(boost::asio::ssl::context::sslv23)
{
	_engine = new SslEngine(_io_service, _ctx);
}

Network::~Network() {
}


/* SETTER */

void Network::setPort(uint16_t port) {
	_port = port;
}

void Network::setIP(const std::string& ip) {
	_ip = ip;
}


/* GETTER */

const uint16_t Network::getPort() {
	return (_port);
}

const std::string& Network::getIP() {
	return (_ip);
}

