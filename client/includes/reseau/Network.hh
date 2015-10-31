#ifndef NETWORK_H_
# define NETWORK_H_

# include "SslEngine.hh"
# include "Packager.h"
# include "debug.hh"

class Network
{
private:
	std::string _port;
	std::string _ip;

	boost::asio::io_service _ios;
	boost::asio::ssl::context _ctx;
	boost::asio::ip::tcp::resolver::iterator _iterator;
	boost::shared_ptr<ISocketEngine>	_socket;

	Packager *_packager;
	SslEngine *_engine;

public:
	Network(const std::string& port = "1234", const std::string& ip = "127.0.0.1", Packager* packager = nullptr);
	virtual ~Network();

	void initNetwork();
	void networkLoop();
};

#endif /* !NETWORK_H_ */