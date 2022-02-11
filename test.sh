y=3
x=1
clear
echo "
 _____ _____   ____ ___  _   _ _____  _    ___ _   _ _____ ____  ____  
|  ___|_   _| / ___/ _ \| \ | |_   _|/ \  |_ _| \ | | ____|  _ \/ ___| 
| |_    | |  | |  | | | |  \| | | | / _ \  | ||  \| |  _| | |_) \___ \ 
|  _|   | |  | |__| |_| | |\  | | |/ ___ \ | || |\  | |___|  _ < ___) |
|_|     |_|___\____\___/|_| \_| |_/_/   \_\___|_| \_|_____|_| \_\____/ 
         |_____|                                                       

		valgrind"
echo

while [ $x -le $y ]
do
	echo "#include <iostream>
		  #include <string>
		  #include <stdlib.h>
		  #include <deque>
		  #include <map>
		  #include <stack>
		  #include <vector>
		  #include <iterator>
		  #include <exception>
		  #include <type_traits>
		  namespace ft = std;" > original.cpp
	tail -n +5 main.cpp >> original.cpp
	make re ;
	./ft_containers > out_ft
	if [ $? -ne 0 ]
	then
		echo -e "\033[31m    KO \033[m"
		y=-1
		break
	fi
	./std_containers > out_std
	diff out_ft out_std
	if [ $? -ne 0 ]
	then
		echo -e "\033[31m    KO \033[m"
		y=-1
		break
	fi
	echo -ne "\033[32m \t   $x/$y OK \033[m"\\r
	x=$(( x + 1 ))
done

if [ $y -ne -1 ]
then
	clear
	echo -e "\033[32m/*************************\ \n|*			 *| \n|*      Congrats	 *| \n|*	$y/$y		 *| \n|*			 *| \n\\*************************/ \033[m"
fi

rm out_ft
rm out_std
