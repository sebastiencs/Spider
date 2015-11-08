##
## Makefile<plugins> for epitech in /home/chapui_s/rendu/
##
## Made by chapui_s
## Login   <chapui_s@epitech.eu>
##
## Started on  Sat Nov  7 15:55:46 2015 chapui_s
## Last update Sat Nov  7 15:55:46 2015 chapui_s
##

NAME			= ../HttpPost.so

SRC			= HttpPost.cpp				\
			  ../../../common/src/paquetKeys.cpp	\
			  ../../../common/src/paquetMouse.cpp	\
			  ../../../common/src/paquet.cpp

OBJ			= $(SRC:.cpp=.o)

DIR_COMMON		= ../../../common

INCLUDES		= -I ../../includes -I $(DIR_COMMON)/includes

CXX			= clang++

RM			= rm -f

override CXXFLAGS	+= -std=c++11 -Wall -Wextra $(INCLUDES) -fPIC

LDLIBS			= -lboost_system -lboost_coroutine -lboost_filesystem -lboost_date_time -lboost_thread -lssl -lcrypto -lcurl -ldl -Wl,--export-dynamic -rdynamic -shared

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
