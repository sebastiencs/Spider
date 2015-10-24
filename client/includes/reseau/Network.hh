

#ifndef NETWORK_H_
# define NETWORK_H_

# include <boost/cstdint.hpp>
# include "ISocketEngine.hh"

class Network : public ISocketEngine
{
private:
	uint16_t _port;
	uint32_t _ip;
	boost::shared_ptr<ISocketEngine> _socket;

public:
	Network(uint16_t port = 0, uint32_t ip = 0);
	virtual ~Network();

	void doHandshake(boost::asio::ssl::stream_base::handshake_type, const std::function<void()> &);
	void async_read(void *, size_t, const std::function<void()> &);
	void async_write(void *, size_t, const std::function<void()> &);
	void async_read_some(void *, size_t, const std::function<void()> &);
	void async_write_some(void *, size_t, const std::function<void()> &);
	void handleError(const std::function<void()> &) = 0;

	void setPort(uint16_t port);
	void setIP(uint32_t ip);

	const uint16_t getPort();
	const uint32_t getIP();

};

#endif /* !NETWORK_H_ */