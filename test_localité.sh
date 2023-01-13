echo $#
echo $@

recurrence=0


fct_G()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>1.5 && $10<6.5 && $11<-50 && $11>-55){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

fct_F()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>40 && $10<52 && $11>4 && $11<6){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

fct_A()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>11 && $10<18 && $11>-63 && $11<-59){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

fct_S()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>46 && $10<52 && $11>-60 && $11<-51){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

fct_O()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>-60 && $10<-9 && $11>36 && $11<90){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

fct_Q()
{
	if [ $recurrence -gt 0 ]
	then 
		echo "you cannot select more than one location, please try again"
	else
		cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10<-60 && $11<50){print $0}}' > localisation.txt 
		recurrence=$((recurrence+1))
	fi
}

for var in $@; do
	case $var in
		"-G") fct_G ;;
		
		"-F") fct_F ;;
		
		"-A") fct_A ;;
		
		"-S") fct_S ;;
		
		"-O") fct_O ;;
		
		"-Q") fct_Q ;;
		
		*) cat meteo_filtered_data_v1.csv > localisation.txt ;;
	esac 
done
