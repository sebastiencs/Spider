//
// server.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Oct 10 08:22:24 2015 chapui_s
// Last update Sat Oct 10 08:22:24 2015 chapui_s
//

#include "paquetKeys.hh"
#include "paquetMouse.hh"
#include "paquetFirstServer.hh"

int		main()
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

  std::cout << "\n\n";

  PaquetFirstServer	c;

  c.setReponse(1);

  c.createPaquet();

  c.dumpPaquetHexa();

  std::cout << "Reponse: " << (int)c.getReponse() << std::endl;

  c.dumpPaquet();

  return (0);
}
