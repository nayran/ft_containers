NAME = ft_containers
NAME1 = std_containers

SRCS = main.cpp

FLAGS = -g -Wall -Werror -Wextra

all: print containers

print:
	clear
	@echo " \
_____ _____   ____ ___  _   _ _____  _    ___ _   _ _____ ____  ____ \n\
|  ___|_   _| / ___/ _ \\| \\ | |_   _|/ \\  |_ _| \\ | | ____|  _ \\/ ___| \n\
| |_    | |  | |  | | | |  \\| | | | / _ \\  | ||  \\| |  _| | |_) \\___ \\ \n\
|  _|   | |  | |__| |_| | |\\  | | |/ ___ \\ | || |\\  | |___|  _ < ___) | \n\
|_|     |_|___\\____\\___/|_| \\_| |_/_/   \\_\\___|_| \\_|_____|_| \\_\\____/ \n\
         |_____|"

OBJS = $(SRCS:.cpp=.o)

containers: $(OBJS) 
	@clang++ $(OBJS) -std=c++98 -o $(NAME)
	@clang++ $(OBJS) -DSTL=1 -o $(NAME1)

%.o: %.cpp 
	@clang++ $(FLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(NAME) $(NAME1)

re: clean all

.PHONY: all clean re 
