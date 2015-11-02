#ifndef _HTTP_HH_
# define _HTTP_HH_

# include <string>
# include <curl/curl.h>
# include "paquetMouse.hh"
# include "paquetKeys.hh"
# include "debug.hh"

class		HttpPost
{
public:
  HttpPost();
  ~HttpPost();
  bool		postPaquet(PaquetKeys *paquet, const std::string &name);
  bool		postPaquet(PaquetMouse *paquet, const std::string &name);

private:
  CURL		*curl;
  CURLcode	res;
};

#endif /* !_HTTP_HH_ */
