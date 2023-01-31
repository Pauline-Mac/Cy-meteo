#!/bin/bash

##   ${!i}  permt de réutiliser la valeur de i comme nom de variable

t1=0
t2=0
p1=0
h=0
m=0

i=$#
arg_list=$@
file=not_define

while [ $# -gt 0 ] ; do
	case "$1" in
	-f) file=$2 ;;
	esac 
shift 
done


if [ ! -e $file ]
then
    echo "le fichier n'existe pas"
    exit 1
fi

echo $i
echo $arg_list


recurrence=0

sort=abr

reverse=

## localisation

fct_return()
{
	echo "error occured when executing -" $1
	exit 1	
}


fct_G()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>'"1.5"' && $10<'"6.5"' && $11<'"-50"' && $11>'"-55"'){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'G'
		fi
		recurrence=$((recurrence+1))
	fi
}

fct_F()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>40 && $10<52 && $11>4 && $11<6){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'F'
		fi
		recurrence=$((recurrence+1))
	fi
}

fct_A()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>11 && $10<18 && $11>-63 && $11<-59){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'A'
		fi
		recurrence=$((recurrence+1))
	fi
}

fct_S()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>46 && $10<52 && $11>-60 && $11<-51){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'S'
		fi
		recurrence=$((recurrence+1))
	fi
}

fct_O()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>-60 && $10<-9 && $11>36 && $11<90){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'O'
		fi
		recurrence=$((recurrence+1))
	fi
}

fct_Q()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10<-60 && $11<50){print $0}}' > localisation.txt 
		if [ $? -ne 0 ] ; then
			fct_return 'Q'
		fi
		recurrence=$((recurrence+1))
	fi
}

for var in $arg_list; do
	case $var in
		"-G") fct_G ;;
		
		"-F") fct_F ;;
		
		"-A") fct_A ;;
		
		"-S") fct_S ;;
		
		"-O") fct_O ;;
		
		"-Q") fct_Q ;;
		
		*) if [ $recurrence -eq 0 ] ; then
			cat $file > localisation.txt
		fi ;;
	esac 
done



## mods

fct_t1()
{
	if [ $t1 -gt 0 ]
	then 
		echo $t1
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,13,14 localisation.txt > t1.txt
		t1=$((t1+1))
		echo $reverse
		
	fi
}

fct_t2()
{
	if [ $t2 -gt 0 ]
	then 
		echo $t2
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,2,13,14 localisation.txt | tr -d '-' 'T' > t2.txt
		t3=$((t3+1))
	fi
}

fct_t3()
{
	if [ $t3 -gt 0 ]
	then 
		echo $t3
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,2,13,14 localisation.txt > t3.txt
		t3=$((t3+1))
	fi
}

fct_p1()
{
	if [ $p1 -gt 0 ]
	then 
		echo $p1
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,7 localisation.txt > pression.txt
		p1=$((p1+1))
	fi
}

fct_h()
{
	if [ $h -gt 0 ]
	then 
		echo $h
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,15 localisation.txt > altitude.txt
		h=$((h+1))
	fi
}

fct_m()
{
	if [ $m -gt 0 ]
	then 
		echo $m
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,6 localisation.txt > humidite.txt
		m=$((m+1))
	fi
}

fct_w()
{
	if [ $m -gt 0 ]
	then 
		echo $m
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,4,5 localisation.txt > vent.txt
		m=$((m+1))
	fi
}




## type of sort we will be using and if the sorting will be done in reverse
for var in $arg_list; do
	case $var in
		"--abr") sort=abr ;;
		"--avl") sort=avl ;;
		"--tab") sort=tab ;;
		"-r") reverse=yes ;;
	esac
done






for var in $arg_list; do
	case $var in
		"-t1") fct_t1 ;;
		"-t2") fct_t2 ;;
		"-t3") fct_t3 ;;
		"-p1") fct_p1 ;;
		"-h") fct_h ;;
		"-m") fct_m ;;
		"-w") fct_w ;;

	esac 
done

echo $sort
