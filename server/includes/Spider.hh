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
# include "debug.hh"

class		Spider : public boost::enable_shared_from_this<Spider>
{
public:
  Spider();
  virtual ~Spider();
};


#endif /* !SPIDER_H_ */
