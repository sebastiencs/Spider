#ifndef NETWORK_H_
# define NETWORK_H_

# include "SslEngine.hh"

class Network
{
private:
	uint16_t _port;
	std::string _ip;

	boost::asio::io_service _io_service;
	boost::asio::ssl::context _ctx;

	SslEngine *_engine;

public:
	Network(uint16_t port = 0, const std::string& ip = "127.0.0.1");
	virtual ~Network();

	void setPort(uint16_t port);
	void setIP(const std::string& ip);

	const uint16_t getPort();
	const std::string& getIP();
};

#endif /* !NETWORK_H_ */