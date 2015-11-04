#ifndef NETWORK_H_
# define NETWORK_H_

# include <map>
# include <functional>
# include "SslEngine.hh"
# include "Packager.h"
# include "debug.hh"

class Network
{
private:
	int _pause;

	std::string _port;
	std::string _ip;

	std::map<int, std::function<void (Network& net)> > _response;

	boost::asio::io_service _ios;
	boost::asio::ssl::context _ctx;
	boost::asio::ip::tcp::resolver::iterator _iterator;

	Packager *_packager;
	SslEngine *_engine;

public:
	Network(const std::string& port = "1234", const std::string& ip = "127.0.0.1", Packager* packager = nullptr);
	virtual ~Network();

	int getPause() {
		return (_pause);
	}
	Packager& getPackager() {
		return (*_packager);
	}

	void setPause(int i) {
		_pause = i;
	}

	void sendFirstPaquet(boost::asio::yield_context yield);
	void initNetwork();
	void writeLoop(boost::asio::yield_context yield);
	void readLoop();
};

void spider_exit(Network& net);
void spider_remove(Network& net);
void spider_pause(Network& net);

#endif /* !NETWORK_H_ */
