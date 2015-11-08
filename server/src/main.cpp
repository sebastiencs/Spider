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

int		test()
{
  PaquetKeys	a;

  a.setDate(2010);
  a.setActive("Coucou");
  a.setText("Mon Texte");

  a.createPaquet();

  a.dumpPaquetHexa();

  std::cout << "date: " << a.getDate() << std::endl;
  std::cout << "active: " << a.getActive() << std::endl;
  std::cout << "text: " << a.getText() << std::endl;

  a.dumpPaquet();
  std::cout << a;

  std::cout << "\n\n";

  PaquetMouse	b;

  b.setDate(2010);
  b.setActive("Fenetre ABC");
  b.setX(10);
  b.setY(200);
  b.setButton(3);

  b.createPaquet();

  b.dumpPaquetHexa();

  std::cout << "date: " << b.getDate() << std::endl;
  std::cout << "Active: " <<  b.getActive() << std::endl;

  b.dumpPaquet();
  std::cout << b;

  std::cout << "\n\n";

  PaquetFirstServer	c;

  c.setReponse(1);

  c.createPaquet();

  c.dumpPaquetHexa();

  std::cout << "Reponse: " << (int)c.getReponse() << std::endl;

  c.dumpPaquet();
  std::cout << c;

  return (0);
}
