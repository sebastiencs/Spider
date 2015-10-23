//
// Spider.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Wed Oct 21 09:14:52 2015 chapui_s
// Last update Wed Oct 21 09:14:52 2015 chapui_s
//

#ifndef SPIDER_H_
# define SPIDER_H_

# include <boost/shared_ptr.hpp>
# include <boost/enable_shared_from_this.hpp>
# include "ISocketEngine.hh"
# include "debug.hh"

class	Web;

class					Spider : public boost::enable_shared_from_this<Spider>
{
private:
  boost::shared_ptr<ISocketEngine>	_socket;
  Web					&_web;
  char					_buffer[2048];

public:
  Spider(const boost::shared_ptr<ISocketEngine> &, Web &);
  virtual ~Spider();

  void		prepareFirstConnection();
  void		doFirstConnection();
  void		finish();
  void		dieInDignity();
};

#endif /* !SPIDER_H_ */
