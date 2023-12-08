#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import mraa
import time

pin = 3  # set pin num

try:
    gpio = mraa.Gpio(pin)
    gpio.dir(mraa.DIR_IN)  # set mode as input

    while True:
        value = gpio.read()  # read from pin 3
        print("value: {}".format(value))
        time.sleep(1)
        
except KeyboardInterrupt:
    print("\nstop\n")
