#!/usr/bin/env python
#
#	Copyright (c) 2016 CurlyMo <curlymoo1@gmail.com>
#
#  This Source Code Form is subject to the terms of the Mozilla Public
#  License, v. 2.0. If a copy of the MPL was not distributed with this
#  file, You can obtain one at http://mozilla.org/MPL/2.0/.
#

import os
import sys
from time import sleep
from wiringX import gpio

gpio.setup(gpio.ROCK4);

gpio.pinMode(gpio.PIN8, gpio.PINMODE_INPUT);

try:
	while True:
		print "Reading from pin 8: "+str(gpio.digitalRead(gpio.PIN8));
		sleep(1);
		print "Reading from pin 8: "+str(gpio.digitalRead(gpio.PIN8));
		sleep(1);
except KeyboardInterrupt:
	pass
