##
## Makefile for epitech in /home/chapui_s/rendu/
##
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
##
## Started on  Sat Oct 10 08:18:01 2015 chapui_s
## Last update Sat Oct 10 08:18:01 2015 chapui_s
##

NAME			= server

DIR_COMMON		= ../common

SRC			= src/server.cpp				\
			  $(DIR_COMMON)/src/paquet.cpp			\
			  $(DIR_COMMON)/src/paquetKeys.cpp		\
			  $(DIR_COMMON)/src/paquetMouse.cpp		\
			  $(DIR_COMMON)/src/paquetCommandServer.cpp	\
			  $(DIR_COMMON)/src/paquetCommandClient.cpp	\
			  $(DIR_COMMON)/src/paquetFirstServer.cpp	\
			  $(DIR_COMMON)/src/paquetFirstClient.cpp

OBJ			= $(SRC:.cpp=.o)

INCLUDES		= -I ./includes -I $(DIR_COMMON)/includes

CC			= g++

RM			= rm -f

override CXXFLAGS	+= -Wall -Wextra $(INCLUDES) -ggdb

$(NAME):	$(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

all:		$(NAME)

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
