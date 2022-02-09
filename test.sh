y=10
clear
echo "
 _____ _____   ____ ___  _   _ _____  _    ___ _   _ _____ ____  ____  
|  ___|_   _| / ___/ _ \| \ | |_   _|/ \  |_ _| \ | | ____|  _ \/ ___| 
| |_    | |  | |  | | | |  \| | | | / _ \  | ||  \| |  _| | |_) \___ \ 
|  _|   | |  | |__| |_| | |\  | | |/ ___ \ | || |\  | |___|  _ < ___) |
|_|     |_|___\____\___/|_| \_| |_/_/   \_\___|_| \_|_____|_| \_\____/ 
         |_____|                                                       "
echo
for (( x=1; x <= $y; x++ )); do
	echo "#include <iostream>
		  #include <string>
		  #include <stdlib.h>
		  #include <deque>
		  #include <map>
		  #include <stack>
		  #include <vector>
		  #include <iterator>
		  #include <exception>
		  namespace ft = std;" > original.cpp
	tail -n +5 main.cpp >> original.cpp
	make re ; ./ft_containers > out_ft
	#echo "$x: $?"
	if [ $? -ne 0 ]
	then
		echo -e "\e[1;31m    KO \e[0m"
		y=-1
		break
	fi
	./std_containers > out_std
	diff out_ft out_std
	if [ $? -ne 0 ]
	then
		echo -e "\e[1;31m   KO \e[0m"
		y=-1
		break
	fi
	echo -ne "\e[1;32m \t   $x/$y OK \e[0m"\\r
done
clear

if [ $y -ne -1]
then
	echo -e "\e[1;32m/*************************\ \n|*			 *| \n|*      Congrats	 *| \n|*	$y/$y		 *| \n|*			 *| \n\\*************************/ \e[0m"
fi

rm out_ft
rm out_std
