# Cy-meteo
project info

Welcome to our meteo project !

You can find down below a list of the arguments you can use and what is essential for the program. Some of them are mandatory for our program to work correctly : 

Mandatory :
  -f<filename.csv> with filename the file with the data necessary
  
  and at least one option :
  -t1 : produce an error bar schema with temperatures, min, max and average
  -t2 : produce a line diagram with temperature sorted and assiociated to dates
  -p1 : same as t1 but with pressure
  -p2 : same as t2 but with pressure
  -w  : produce a vector diagram with the wind direction and the coordinates of the stations
  -h  : produce an "height map"
  -m  : same as h but with moisture

PLEASE DO NOT USE MORE THAN ONCE AN ARGUMENT AND SELECT A CORRECT DATA FILE !

GNUPLOT IS REQUIRED, you will need to install it if not already done and to copy ALL the files from the GitHub.

Optional :
  location (will take the data from a particular region) :
    -G : Guyana
    -O : Indian Ocean
    -S : Saint-Pierre et Michelon
    -F : Metropolitan France with Corisica 
    -A : "Antilles"
  if there is no location precised, all the data will be used
  
  type of sort used in the c langage program :
  --avl : Sorting will be done with automatically balanced binary search trees
  --abr : Sorting will be done with binary search trees
  --tab : Sorting will be done with a list
  If nothing is precised, the sorting will be done with avl (default sort)
  
  
  --help will write this readme in the terminal

RUNNING THE PROGRAM :
To run the program, you will need to use 'bash program.sh ...'  or use the command 'chmod +x program.sh' to give the execution right to the program and the ./program.sh ...


THANKS FOR USING OUR PROGRAM, WE HOPE YOU WILL ENJOY THE RESULTS

CLEMENT LE COADOU AND PAULINE MACEIRAS CY TECH
 
