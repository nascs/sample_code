#!/bin/bash

num=63

echo $num > /sys/class/gpio/export
echo "out" > /sys/class/gpio/gpio$num/direction

while true
do
	echo 1 > /sys/class/gpio/gpio$num/value
	echo 0 > /sys/class/gpio/gpio$num/value
done
