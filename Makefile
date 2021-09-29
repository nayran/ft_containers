NAME = ft_containers

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98

$(NAME): $(OBJS)
	@clang++ $(OBJS) -o $(NAME)

%.o: %.cpp $(HEAD)
	@clang++ $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean re
