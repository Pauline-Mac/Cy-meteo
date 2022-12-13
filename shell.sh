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

## tri 

recur=0
echo $#
echo $@
for var in $@; do
	if [ $var == "-a" ] ; then
		echo 'argument 0'
		recur=$((recur+1))
		sort -t";" -k2 meteo_filtered_data_v1.csv | cut 
	else 
		echo 'noooonnn'
	fi
	if [ $recur -gt 1 ] ; then
		echo $recur
		return 1
	fi
done
