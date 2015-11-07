//
// HttpPost.hh for includes in /home/bresci_b/rendu/Spider/server/src
//
// Made by bresci_b bresci_b
// Login   <bresci_b@epitech.net>
//
// Started on  Tue Oct 27 11:35:15 2015 bresci_b bresci_b
// Last update Tue Oct 27 17:16:43 2015 bresci_b bresci_b
//

#ifndef _HTTP_HH_
# define _HTTP_HH_

# include <string>
# include <curl/curl.h>
# include "paquetMouse.hh"
# include "paquetKeys.hh"
# include "debug.hh"

# define HOST_NAME	"spidermen.herokuapp.com"
# define PAQUET_KEYS	"/paquet_keys"
# define PAQUET_MOUSE	"/paquet_mouses"

class			HttpPost
{
public:
  HttpPost();
  ~HttpPost();
  bool			postPaquet(PaquetKeys *paquet, const std::string &name);
  bool			postPaquet(PaquetMouse *paquet, const std::string &name);

private:
  std::string		createRequest(PaquetKeys *paquet, const std::string &name);
  std::string		createRequest(PaquetMouse *paquet, const std::string &name);
  CURL			*_curl;
  CURLcode		_res;
};

#endif /* !_HTTP_HH_ */
