//
// server.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Oct 10 08:22:24 2015 chapui_s
// Last update Sat Oct 10 08:22:24 2015 chapui_s
//

#include <boost/lexical_cast.hpp>
#include "paquetKeys.hh"
#include "paquetMouse.hh"
#include "paquetFirstServer.hh"
#include "Server.hh"

int		main(int argc, char **argv)
{
  uint16_t	port = 0;

  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <port>" << std::endl;
    return (-1);
  }

  try {
    port = boost::lexical_cast<uint16_t>(argv[1]);
  } catch (const boost::bad_lexical_cast &) {
    std::cerr << "error: Wrong port value" << std::endl;
    return (-1);
  }

  try {

    std::unique_ptr<Server>	server(new Server(port));

    server->start();


  } catch (const std::exception &e) {
    std::cerr << "Exception : " << e.what() << std::endl;
  }

  return (0);
}
