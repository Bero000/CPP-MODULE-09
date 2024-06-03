NAME = RPN

CC = c++

CXXFLAGS = -Wall -Werror -Wextra -std=c++98

RM = rm -rf

SRC = main.cpp RNP.cpp
		
OBJ = $(SRC:.cpp=.o)

$(NAME): $(OBJ)
	@$(CC) $(CCXFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

r:re
c:clean
f:fclean