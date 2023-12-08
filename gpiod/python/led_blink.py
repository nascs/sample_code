#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import gpiod
import time

chip_name = "gpiochip3"
line_offset = 4

chip = gpiod.chip(chip_name)
line = chip.get_line(line_offset)

config = gpiod.line_request()
config.consumer = "GPIO3_A4_Blink"
config.request_type = gpiod.line_request.DIRECTION_OUTPUT

line.request(config)

print(line.consumer)

while True:
    line.set_value(0)
    time.sleep(0.1)
    line.set_value(1)
    time.sleep(0.1)
