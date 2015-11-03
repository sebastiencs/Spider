#include "debug.hh"
#include "HttpPost.hh"

HttpPost::HttpPost()
{
  DEBUG_MSG("HttpPost");
  curl_global_init(CURL_GLOBAL_ALL);
  _curl = curl_easy_init();
}

HttpPost::~HttpPost()
{
  DEBUG_MSG("HttpPost");
  if (_curl)
    curl_easy_cleanup(_curl);
  curl_global_cleanup();
}

bool	HttpPost::postPaquet(PaquetKeys *paquet, const std::string &name)
{
  std::string	url = HOST_NAME;

  url += PAQUET_KEYS;
  if (!_curl || !paquet)
    return false;
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, createRequest(paquet, name).c_str());
  _res = curl_easy_perform(_curl);
  if (_res != CURLE_OK)
    {
      std::cerr << "here PaquetKeys" << std::endl;
      std::cerr << curl_easy_strerror(_res) << std::endl;
      return false;
    }
  return true;
}

bool	HttpPost::postPaquet(PaquetMouse *paquet, const std::string &name)
{
  std::string	url = HOST_NAME;

  url += PAQUET_MOUSE;
  if (!_curl || !paquet)
    return false;
  curl_easy_setopt(_curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, createRequest(paquet, name).c_str());
  _res = curl_easy_perform(_curl);
  if (_res != CURLE_OK)
    {
      std::cerr << "here - PaquetMouse" << std::endl;
      std::cerr << curl_easy_strerror(_res) << std::endl;
      return false;
    }
   return true;
}

std::string	HttpPost::createRequest(PaquetKeys *paquet, const std::string &name)
{
  std::string	request;

#ifdef DEBUG
  std::cerr << request << std::endl;
#endif /* !DEBUG */

  return request;
}

std::string	HttpPost::createRequest(PaquetMouse *paquet, const std::string &name)
{
  std::string	request;

#ifdef DEBUG
  std::cerr << request << std::endl;
#endif /* !DEBUG */

  return request;
}
