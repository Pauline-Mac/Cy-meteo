echo $#
echo $@
L=0
for var in $@; do
	case $var in
		"-G") cat meteo_filtered_data_v1.csv | tr  ',' ';' | awk -F ';' '{if($10>=0 && $11>=0){print $0}}' > localisation.txt
	esac 
done
