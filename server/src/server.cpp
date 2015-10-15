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

int		main()
{
  PaquetKeys	a;

  a.setDate(2010);
  a.setActive("Coucou");
  a.setText("Mon Texte");

  a.createPaquet();

  a.dumpPaquetHexa();

  std::cout << a.getDate() << std::endl;
  std::cout << a.getActive() << std::endl;
  std::cout << a.getText() << std::endl;

  a.dumpPaquet();

  PaquetMouse	b;

  b.setDate(2010);
  b.setActive("Fenetre ABC");
  b.setX(10);
  b.setY(200);
  b.setButton(3);

  b.createPaquet();

  b.dumpPaquetHexa();

  std::cout << b.getDate() << std::endl;
  std::cout << b.getActive() << std::endl;

  b.dumpPaquet();

  return (0);
}
