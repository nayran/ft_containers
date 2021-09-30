NAME = ft_containers
NAME1 = std_containers

SRCS = main.cpp original.cpp

OBJS = $(SRCS:.cpp=.o)

FLAGS = -Wall -Werror -Wextra -std=c++98

all: $(NAME)

$(NAME): $(OBJS)
	@clang++ main.o -o $(NAME)
	@clang++ original.o -o $(NAME1)

%.o: %.cpp $(HEAD)
	@clang++ $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(NAME) $(NAME1)

re: clean all

.PHONY: all clean re
