for (( x=0; x <= 24; x++ )); do
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
	echo "$x: $?"
	if [ $? -ne 0 ]
	then
		break
	fi
	./std_containers > out_std
	diff out_ft out_std
	if [ $? -ne 0 ]
	then
		break
	fi
done
rm out_ft
rm out_std
