#ifndef NETWORK_H_
# define NETWORK_H_

# include <map>
# include <functional>
# include "SslEngine.hh"
# include "Packager.h"
# include "Startup.hh"
# include "debug.hh"

class Network
{
private:
	int _pause;

	Startup		_startup;
	std::string _port;
	std::string _ip;

	std::map<int, std::function<void (boost::asio::yield_context yield)> > _response;

	boost::asio::io_service _ios;
	boost::asio::ssl::context _ctx;
	boost::asio::ip::tcp::resolver::iterator _iterator;

	Packager *_packager;
	SslEngine *_engine;

public:
	Network(const std::string& port = "1234", const std::string& ip = "127.0.0.1", Packager* packager = nullptr, const std::string& crt = "client.crt");
	virtual ~Network();

	int getPause() {
		return (_pause);
	}
	SslEngine& getEngine() {
		return (*_engine);
	}

	void setPause(int i) {
		_pause = i;
	}

	void spider_switchStartup(Network &net, boost::asio::yield_context yield);
	void sendFirstPaquet(boost::asio::yield_context yield);
	void initNetwork();
	void writeLoop(boost::asio::yield_context yield);
	void readLoop(boost::asio::yield_context yield);
	void spider_exit(Network& net, boost::asio::yield_context yield);
	void spider_remove(Network& net, boost::asio::yield_context yield);
	void spider_pause(Network& net, boost::asio::yield_context yield);
};


#endif /* !NETWORK_H_ */
