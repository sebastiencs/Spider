#ifndef NETWORK_H_
# define NETWORK_H_

# include "SslEngine.hh"
# include "debug.hh"

class Network
{
private:
	std::string _port;
	std::string _ip;
	int _isConnected;

	boost::asio::io_service _ios;
	boost::asio::ssl::context _ctx;

	boost::asio::ip::tcp::resolver::iterator _iterator;

	boost::shared_ptr<ISocketEngine>	_socket;
	SslEngine *_engine;

public:
	Network(const std::string& = "1234", const std::string& ip = "127.0.0.1");
	virtual ~Network();

	void initNetwork();

	void write(void *data, size_t size);
};

#endif /* !NETWORK_H_ */