##
## Makefile for epitech in /home/chapui_s/rendu/
##
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
##
## Started on  Sat Oct 10 08:18:01 2015 chapui_s
## Last update Tue Oct 27 17:06:55 2015 bresci_b bresci_b
##

NAME			= server

DIR_COMMON		= ../common

SRC			= src/main.cpp					\
			  src/Server.cpp				\
			  src/Spider.cpp				\
			  src/Web.cpp					\
			  src/SslContext.cpp				\
			  src/Acceptor.cpp				\
			  src/Signal.cpp				\
			  src/Buffer.cpp				\
			  src/DumpFile.cpp				\
			  $(DIR_COMMON)/src/paquet.cpp			\
			  $(DIR_COMMON)/src/paquetKeys.cpp		\
			  $(DIR_COMMON)/src/paquetMouse.cpp		\
			  $(DIR_COMMON)/src/paquetCommandServer.cpp	\
			  $(DIR_COMMON)/src/paquetCommandClient.cpp	\
			  $(DIR_COMMON)/src/paquetFirstServer.cpp	\
			  $(DIR_COMMON)/src/paquetFirstClient.cpp	\
			  $(DIR_COMMON)/src/SslEngine.cpp

OBJ			= $(SRC:.cpp=.o)

INCLUDES		= -I ./includes -I $(DIR_COMMON)/includes

CXX			= clang++

RM			= rm -f

override CXXFLAGS	+= -std=c++11 -Wall -Wextra $(INCLUDES) -D CERTIFICATE_FILE=\"ressources/server.crt\" -D PRIVATE_KEY_FILE=\"ressources/server.key\" -D DH_FILE=\"ressources/dh1024.pem\"

LDLIBS			= -lboost_system -lboost_coroutine -lboost_filesystem -lboost_date_time -lboost_thread -lssl -lcrypto -lcurl -ldl

DEPS			= $(OBJ:.o=.d)

$(NAME):	$(OBJ)
		$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) $(LDLIBS)
		make -C ./plugins/HttpPost

-include $(DEPS)

all:		$(NAME)

%.o:		%.cpp
		$(CXX) -c $(CXXFLAGS) -MMD -MF $(patsubst %.o,%.d,$@) -c -o $@ $<

clean:
		$(RM) $(OBJ) $(DEPS)
		make clean -C ./plugins/HttpPost

fclean:		clean
		$(RM) $(NAME)
		make fclean -C ./plugins/HttpPost

re:		fclean all

.PHONY:		all clean fclean re
