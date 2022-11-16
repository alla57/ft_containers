CXX = c++

RM = rm -rf

CXXFLAGS = -Wall -Wextra -Werror -I./ -std=c++98

NAME = Containers

SRC_PATH =	test.cpp		\

SRC = $(SRC_PATH)

OBJ	= $(SRC:.cpp=.o)

all : $(NAME)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

$(NAME) : $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(SRC)

re : fclean all

.PHONY : all clean re