//
// sample.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Sun Nov  8 02:19:56 2015 chapui_s
// Last update Sun Nov  8 02:19:56 2015 chapui_s
//

#ifndef SAMPLE_H_
# define SAMPLE_H_

# include "paquetMouse.hh"
# include "paquetKeys.hh"
# include "debug.hh"
# include "IPlugin.hh"

class			Sample : public IPlugin
{
public:
  Sample();
  virtual ~Sample();
  virtual bool		getKey(PaquetKeys *paquet, const std::string &name);
  virtual bool		getMouse(PaquetMouse *paquet, const std::string &name);
};

#endif /* !SAMPLE_H_ */
