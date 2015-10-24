//
// debug.hh for epitech in /home/chapui_s/rendu/
//
// Made by chapui_s
// Login   <chapui_s@epitech.eu>
//
// Started on  Thu Oct 22 10:59:20 2015 chapui_s
// Last update Thu Oct 22 10:59:20 2015 chapui_s
//

#ifndef DEBUG_H_
# define DEBUG_H_

# ifdef DEBUG
#  define DEBUG_MSG(X) do { std::cerr << X << std::endl; } while (0)
# else
#  define DEBUG_MSG(X)
# endif

#endif /* !DEBUG_H_ */
