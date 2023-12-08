#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import os
import sys
from time import sleep
from wiringX import gpio

gpio.setup(gpio.ROCK4);

gpio.pinMode(gpio.PIN8, gpio.PINMODE_INPUT);

try:
	while True:
		print("Reading from pin 8: "+str(gpio.digitalRead(gpio.PIN8)));
		sleep(1);
		print("Reading from pin 8: "+str(gpio.digitalRead(gpio.PIN8)));
		sleep(1);
except KeyboardInterrupt:
	pass
