//
// IPlugin.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sat Nov  7 15:09:21 2015 chapui_s
// Last update Sat Nov  7 15:09:21 2015 chapui_s
//

#ifndef IPLUGIN_H_
# define IPLUGIN_H_

# include "paquetKeys.hh"
# include "paquetMouse.hh"

class		IPlugin
{
public:
  virtual ~IPlugin() {};

  virtual bool	getKey(PaquetKeys *, const std::string &) = 0;
  virtual bool	getMouse(PaquetMouse *, const std::string &) = 0;
};

#endif /* !IPLUGIN_H_ */
