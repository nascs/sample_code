#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import gpiod
import time

chip_name = "gpiochip3"
line_offset = 4

chip = gpiod.chip(chip_name)
line = chip.get_line(line_offset)

config = gpiod.line_request()
config.consumer = "GPIO3_A4_Input"
config.request_type = gpiod.line_request.DIRECTION_INPUT

line.request(config)


while True:
	print("value = ", line.get_value())
	time.sleep(1)




