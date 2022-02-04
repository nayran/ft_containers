for (( x=0; x <= 10; x++ )); do
	make re ; ./ft_containers > out
	echo "$x: $?"
	if [ $? -ne 0 ]
	then
		break
	fi
done
