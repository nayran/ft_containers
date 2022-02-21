NAME = ft_containers
NAME1 = std_containers

SRCS = main.cpp

# mainstd deve rodar em c++11 pelo is_integral
# a main normal roda em c++98, ver target "containers"
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
	@echo "cat main.cpp > mainstd.cpp"
	@echo "make"
	@echo "./ft_containers > out_ft"
	@echo "./std_containers > out_std"
	@echo "diff out_ft out_std"
	@echo "#include <iostream>" > mainstd.cpp
	@echo "#include <string>" >> mainstd.cpp
	@echo "#include <stdlib.h>" >> mainstd.cpp
	@echo "#include <deque>" >> mainstd.cpp
	@echo "#include <map>" >> mainstd.cpp
	@echo "#include <stack>" >> mainstd.cpp
	@echo "#include <vector>" >> mainstd.cpp
	@echo "#include <iterator>" >> mainstd.cpp
	@echo "#include <exception>" >> mainstd.cpp
	@echo "#include <type_traits>" >> mainstd.cpp
	@echo "#include <ctime>" >> mainstd.cpp
	@echo "namespace ft = std;" >> mainstd.cpp
	@tail -n +4 main.cpp >> mainstd.cpp
	@clang++ $(FLAGS) -c mainstd.cpp -o mainstd.o

OBJS = $(SRCS:.cpp=.o)

containers: $(OBJS) 
	@clang++ main.o -o $(NAME)
	@clang++ mainstd.o -o $(NAME1)
	@./ft_containers > out_ft
	@./std_containers > out_std
	@diff out_ft out_std
	@if [ $$? -ne 0 ]; then 												\
		echo "\033[31m/*************************\\";						\
		echo "|*			 *|";											\
		echo "|*      KO		 *|";										\
		echo "|*			 *|";											\
		echo "\*************************/ \033[m";							\
	else																	\
		echo "\033[32m/*************************\\";						\
		echo "|*			 *|";											\
		echo "|*      Congrats	 *|";										\
		echo "|*			 *|";											\
		echo "\*************************/ \033[m";							\
	fi


%.o: %.cpp 
	@clang++ $(FLAGS) -std=c++98 -c $< -o $@

clean:
	@rm -rf $(OBJS) $(NAME) $(NAME1) mainstd.* out_ft out_std

re: clean all

.PHONY: all clean re 
