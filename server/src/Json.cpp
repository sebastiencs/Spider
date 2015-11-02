//
// Json.cpp for src in /home/bresci_b/rendu/Spider/server/src
//
// Made by bresci_b bresci_b
// Login   <bresci_b@epitech.net>
//
// Started on  Tue Oct 27 11:35:03 2015 bresci_b bresci_b
// Last update Tue Oct 27 17:22:26 2015 bresci_b bresci_b
//

#include "debug.hh"
#include "Json.hh"

Json::Json()
{
  DEBUG_MSG("Json created");
  _file = NULL;
  _name = "";
}

Json::~Json()
{
  DEBUG_MSG("Json deleted");
  if (_file && _file->is_open())
    {
      _file->close();
      delete _file;
    }
  if (!_name.empty())
    _name.clear();
}

void		Json::openFile(const std::string &str)
{
  boost::posix_time::ptime time_now;
  std::string	time = "";
  std::string	file = "";

  _name = str;
  time_now = boost::posix_time::second_clock::local_time();
  time = boost::posix_time::to_simple_string(time_now).c_str();
  std::replace(time.begin(), time.end(), ' ', '-');
  file = str;
  file += "-";
  file += time;
  _file = new std::ofstream(file.c_str(), std::ofstream::out);
}

bool		Json::checkFileExist() const
{
  if (_file && _file->is_open())
    return true;
  return false;
}

std::string	Json::getName() const
{
  return _name;
}

bool		Json::writePaquetKeys(PaquetKeys *paquet)
{
  std::string active = "";
  std::string text = "";

  if (!paquet)
    return false;
  if (checkFileExist())
    {
      active = (paquet->getActive()) ? (paquet->getActive()) : (std::string());
      text = (paquet->getText()) ? (paquet->getText()) : (std::string());
      *_file << "PaquetKeys = {name: " << getName();
      *_file << ", date: " << paquet->getDate();
      *_file << ", sizeActive: " << active.size();
      if (!active.empty())
	*_file << ", active: " << active;
      *_file << ", sizeText: " << text.size();
      if (!text.empty())
	*_file << ", text: " << text;
      *_file << "}" << std::endl;
      return true;
    }
  return false;
}

bool		Json::writePaquetMouse(PaquetMouse *paquet)
{
  std::string active = "";

  if (!paquet)
    return false;
  if (checkFileExist())
    {
      active = (paquet->getActive()) ? (paquet->getActive()) : (std::string());
      *_file << "PaquetMouse = {name: " << getName();
      *_file << ", date: " << paquet->getDate();
      *_file << ", sizeActive: " << active.size();
      if (!active.empty())
	*_file << ", active: " << active;
      *_file << ", X: " << paquet->getX();
      *_file << ", Y: " << paquet->getY();
      *_file << ", Button: " << static_cast<int>(paquet->getButton());
      *_file << ((paquet->getButton() == 1) ? ("(Left)") : ((paquet->getButton() == 2) ? ("(Middle)") : ("(Right)")));
      *_file << "}" << std::endl;
    }
  return false;
}
