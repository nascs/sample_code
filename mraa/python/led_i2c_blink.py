#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import mraa
import time

# initialise I2C
x = mraa.I2c(2)
x.address(0x20)
while True:
	x.writeReg(0x11, 0x01)
	time.sleep(0.5)
	x.writeReg(0x12, 0x02)
	time.sleep(0.5)
	x.writeReg(0x13, 0x03)
	time.sleep(0.5)
	x.writeReg(0x14, 0x04)
	time.sleep(0.5)
	x.writeReg(0x15, 0x05)
	time.sleep(0.5)
	x.writeReg(0x16, 0x06)
