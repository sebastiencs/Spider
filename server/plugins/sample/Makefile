##
## Makefile for epitech in /home/chapui_s/rendu/
##
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
##
## Started on  Sun Nov  8 02:23:05 2015 chapui_s
## Last update Sun Nov  8 02:23:05 2015 chapui_s
##

NAME			= ../Sample.so

SRC			= sample.cpp

OBJ			= $(SRC:.cpp=.o)

DIR_COMMON		= ../../../common

INCLUDES		= -I ../../includes -I $(DIR_COMMON)/includes

CXX			= clang++

RM			= rm -f

override CXXFLAGS	+= -std=c++11 -Wall -Wextra $(INCLUDES) -fPIC

LDLIBS			= -Wl,--export-dynamic -rdynamic -shared

DEPS			= $(OBJ:.o=.d)

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)

-include $(DEPS)

all:		$(NAME)

%.o:		%.cpp
		$(CXX) -c $(CXXFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -c -o $@ $<

clean:
		$(RM) $(OBJ) $(DEPS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
