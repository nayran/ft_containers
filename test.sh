x=0
while [x < 10] do
	make re ;
	./ft_containers > out
	if $? != 0
	then
		break
	fi
	x++
done
