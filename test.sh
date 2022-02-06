for (( x=0; x <= 10; x++ )); do
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
