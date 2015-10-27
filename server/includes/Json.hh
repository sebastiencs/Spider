//
// Json.hh for includes in /home/bresci_b/rendu/Spider/server/src
//
// Made by bresci_b bresci_b
// Login   <bresci_b@epitech.net>
//
// Started on  Tue Oct 27 11:35:15 2015 bresci_b bresci_b
// Last update Tue Oct 27 17:16:43 2015 bresci_b bresci_b
//

#ifndef _JSON_HH_
# define _JSON_HH_

# include <string>
# include <iostream>
# include <iostream>
# include <fstream>
# include <boost/asio.hpp>
# include <boost/date_time/posix_time/posix_time.hpp>
# include <boost/date_time/posix_time/posix_time_io.hpp>
# include "paquetMouse.hh"
# include "paquetKeys.hh"

class		Json
{
public:
  Json();
  ~Json();
  void		openFile(const std::string &str);
  bool		checkFileExist() const;
  std::string	getName() const;
  bool		writePaquetKeys(PaquetKeys *paquet);
  bool		writePaquetMouse(PaquetMouse *paquet);

private:
  std::ofstream *_file;
  std::string	_name;
};

#endif /* !_JSON_HH_ */
