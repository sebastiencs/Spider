#include "../../includes/reseau/Network.hh"

Network::Network(uint16_t port, uint32_t ip) :
	_port(port), _ip(ip)
{
	boost::asio::io_service io_service;
	boost::asio::ip::tcp::resolver resolve(io_service);
	
	std::cout << "Network Initialise" << std::endl;
}

Network::~Network() {
	std::cout << "Network closed" << std::endl;
}


/* SETTER */

void Network::setPort(uint16_t port) {
	_port = port;
}

void Network::setIP(uint32_t ip) {
	_ip = ip;
}


/* GETTER */

const uint16_t Network::getPort() {
	return (_port);
}

const uint32_t Network::getIP() {
	return (_ip);
}
