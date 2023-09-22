#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import smbus2
import time

bus = smbus2.SMBus(8)
address = 0x48


while True:
	input_state = bus.read_byte(address)
	print("input_state: ", input_state)
	time.sleep(1)

