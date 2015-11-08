//
// sample.cpp for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov  8 02:18:44 2015 chapui_s
// Last update Sun Nov  8 02:18:44 2015 chapui_s
//

#include "debug.hh"
#include "sample.hh"
#include "IPlugin.hh"

Sample::Sample()
{
  DEBUG_MSG("Sample created");
}

Sample::~Sample()
{
  DEBUG_MSG("Sample deleted");
}

bool	Sample::getKey(PaquetKeys *paquet, const std::string &name)
{
#ifdef DEBUG
  std::cerr << name << << *paquet << std::endl;
#else
  (void)paquet;
  (void)name;
#endif /* !DEBUG */
  return true;
}

bool	Sample::getMouse(PaquetMouse *paquet, const std::string &name)
{
#ifdef DEBUG
  std::cerr << name << << *paquet << std::endl;
#else
  (void)paquet;
  (void)name;
#endif /* !DEBUG */
  return true;
}

extern "C" IPlugin	*loadPlugin()
{
  return (new Sample());
}
