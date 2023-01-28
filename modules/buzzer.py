#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import radxa.rock4
from OPi import GPIO
import time


GPIO.setwarnings(False)
# to define a pin
BeepPin = 3

def setup():
     # Numbers GPIOs by physical location
    GPIO.setmode(radxa.rock4.BOARD) 
    # Set BeepPin's mode is output
    GPIO.setup(BeepPin, GPIO.OUT) 
    # Set BeepPin high(+3.3V) to off beep
    GPIO.output(BeepPin, GPIO.HIGH) 

def loop():
    while True:
        GPIO.output(BeepPin, GPIO.LOW)
        time.sleep(1)
        GPIO.output(BeepPin, GPIO.HIGH)
        time.sleep(1)

def destroy():
    # beep off
    GPIO.output(BeepPin, GPIO.HIGH)
     # Release resource
    GPIO.cleanup()                    

 # Program start from here
if __name__ == '__main__':    
    print("Press Ctrl+C to end the program...")
    setup()
    try:
        loop()
    except KeyboardInterrupt:  # exit with  'Ctrl+C' 
        destroy()