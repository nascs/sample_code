#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import sys
import time
import smbus2
 
sys.modules['smbus'] = smbus2
 
from RPLCD.i2c import CharLCD
 
lcd = CharLCD('PCF8574', address=0x27, port=7, backlight_enabled=False)
 
try:
    print('Press Ctrl-C to stop the program')
    lcd.clear()
    while True:
        lcd.cursor_pos = (0, 0)
        lcd.write_string("Date: {}".format(time.strftime("%Y/%m/%d")))
        lcd.cursor_pos = (1, 0)
        lcd.write_string("Time: {}".format(time.strftime("%H:%M:%S")))
        time.sleep(1)
except KeyboardInterrupt:
    print('close the program')
finally:
    lcd.clear()