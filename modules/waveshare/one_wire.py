#!/usr/bin/env python
############################################### 
# File Name: temperature.py
# Author:Nasca
# Email:nascs@radxa.com
# Created Time: Tue 13 Dec 2022 10:09:54 AM CST
###############################################

import os
import glob
import time
 
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')

#open the file /sys/bus/w1/devices/28*/w1_slave
base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'

# read the file line by line
def read_temp_raw():
	f = open(device_file, 'r')
	lines = f.readlines()
	f.close()
	return lines
 
#6e 01 ff ff 7f ff ff ff ae : crc=ae YES
#6e 01 ff ff 7f ff ff ff ae t=22875
def read_temp():
	lines = read_temp_raw()
	while lines[0].strip()[-3:] != 'YES':
		time.sleep(0.2)
		lines = read_temp_raw()
	equals_pos = lines[1].find('t=')
	if equals_pos != -1:
		temp_string = lines[1][equals_pos+2:]
		temp_c = float(temp_string) / 1000.0
		temp_f = temp_c * 9.0 / 5.0 + 32.0
		return temp_c, temp_f

# (Celsius， Fahrenheit)
while True:
	print(read_temp())	
	time.sleep(1)
