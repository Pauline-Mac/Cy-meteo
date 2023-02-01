#!/bin/bash

## variables for recurrence
t1=0
t2=0
t3=0
p1=0
p2=0
p3=0
h=0
m=0
w=0

## taking the number and the list of arguments in other variables because the while / shift erase them
i=$#
arg_list=$@

## variable to stock the file name
file=not_define

##verifying if the file is precised and if so replace the name in file
while [ $# -gt 0 ] ; do
	case "$1" in
	-f) file=$2 ;; ## the file name is supposed to be after -f
	--help) cat readme.txt ## printing the readme for --help
	exit 1 ;;
	esac 
shift 
done

## verifying the existence of the file
if [ ! -e $file ]
then
    echo "the file does not exist"
    exit 1
fi

make ## makefile
if [ $? -ne 0 ] ; then ## verifying if it worked
	echo "makefile problem detected, please make sure all the .c files are here"
	exit 1
fi

## to erase
echo $i
echo $arg_list

## recurrence for the localisation
recurrence=0

##default sorting type 
sort=abr

## no done by c language
reverse=

## function of return used to see if the command line was executed and if not exit the program
fct_return()
{
	echo "error occured when executing -" $1
	exit 1	
}

## localisation
fct_G()
{
	if [ $recurrence -gt 0 ] ## not possible to have more than one localistion precised
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat $file | tr  ',' ';' | awk -F ';' '{if($10>'"1.5"' && $10<'"6.5"' && $11<'"-50"' && $11>'"-55"'){print $0}}' > localisation.txt ## using awk to take only the localisation wanted with the coordinates
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

## looking in the list of arguments if localisation was precised, if not, all the file is transfered to localisation.txt directly
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
	if [ $t1 -gt 0 ] ## same recurrence than for localisation needed
	then 
		echo $t1
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,12,13,14 localisation.txt > t1.txt ##taking only the column we will be using
		t1=$((t1+1))
		./t1 t1.txt output_t1.txt --$sort ## executing the c program and looking if it succeed to finish without any errors
		
		gnuplot -persist gnp_1.gnp ## writing the gnuplot scheme associated
		
	fi
}

fct_t2()
{
	if [ $t2 -gt 0 ]
	then 
		echo $t2
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,2,13,14 localisation.txt | tr -d '-' > t2.txt
		t2=$((t2+1))
		./t2 t2.txt output_t2.txt --$sort
		
		gnuplot -persist gnp_2.gnp
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
		./t3 t3.txt output_t3.txt --$sort
		
		gnuplot -persist gnp_3.gnp
	fi
}

fct_p1()
{
	if [ $p1 -gt 0 ]
	then 
		echo $p1
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,7 localisation.txt > p1.txt
		p1=$((p1+1))
		./p1 p1.txt output_p1.txt --$sort
		
		gnuplot -persist gnp_1.gnp
	fi
}

fct_p2()
{
	if [ $p2 -gt 0 ]
	then 
		echo $p2
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,2,7 localisation.txt > p2.txt
		p2=$((p2+1))
		./p2 p2.txt output_p2.txt --$sort
		
		gnuplot -persist gnp_2.gnp
	fi
}

fct_h()
{
	if [ $h -gt 0 ]
	then 
		echo $h
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,15 localisation.txt > h.txt
		h=$((h+1))
		./h h.txt output_h.txt --$sort
		
		gnuplot -persist gnp_h.gnp
	fi
}

fct_m()
{
	if [ $m -gt 0 ]
	then 
		echo $m
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,6 localisation.txt > m.txt
		m=$((m+1))
		./m m.txt output_m.txt --$sort
		
		gnuplot -persist gnp_m.gnp
	fi
}

fct_w()
{
	if [ $w -gt 0 ]
	then 
		echo $w
		echo "problem detected too many arguments of the same type"
	else
		cut -d";" -f1,4,5 localisation.txt > w.txt
		w=$((w+1))
		./w w.txt output_w.txt --$sort
		
		gnuplot -persist gnp_w.gnp
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





## arguments
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

## in case not any mods selected, exit
if [ $recurrence -eq 0 ] ; then
	echo "please select an option"
	exit 1
fi

