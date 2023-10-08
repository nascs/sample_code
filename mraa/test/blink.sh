#! /bin/bash

if (( EUID != 0 ))
then
	echo "please run as root."
	exit -1
fi

if [ $# -ne 1 ]; then
	echo "please just input one param !"
	exit 1
fi

counter=0
echo "start to blink pin $1 ..."

for ((i=0; i<5; i++)); do
	echo "pin $1: high"
	sudo mraa-gpio set $1 1
	sleep 1s
	echo "pin $1: low"
	sudo mraa-gpio set $1 0
	sleep 1s

	counter=$((counter+1))
done

exit
