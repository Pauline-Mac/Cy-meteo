#!/bin/bash

##   ${!i}  permt de réutiliser la valeur de i comme nom de variable


##   petit programme pour regarder argument


echo $#
echo $@
for var in $@; do
	if [ $var == "-a" ] ; then
		echo 'argument 0'
	else 
		echo 'noooonnn'
	fi
done
