#ifndef _HTTP_HH_
# define _HTTP_HH_

# include <string>
# include <curl/curl.h>
# include "paquetMouse.hh"
# include "paquetKeys.hh"

class		HttpPost
{
public:
  HttpPost();
  ~HttpPost();
  bool		postPaquetKeys(PaquetKeys *paquet);
  bool		postPaquetMouse(PaquetMouse *paquet);
  
private:
  CURL		*curl;
  CURLcode	res;
};

#endif /* !_HTTP_HH_
