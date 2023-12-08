#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import os
import sys
from time import sleep
from wiringX import gpio

gpio.setup(gpio.ROCK4);

gpio.pinMode(gpio.PIN8, gpio.PINMODE_OUTPUT);

try:
	while True:
		gpio.digitalWrite(gpio.PIN8, gpio.HIGH);
		sleep(1);
		gpio.digitalWrite(gpio.PIN8, gpio.LOW);
		sleep(1);
except KeyboardInterrupt:
	pass
