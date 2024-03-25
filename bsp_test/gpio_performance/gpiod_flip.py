#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import gpiod
import time

chip_name = "gpiochip1"
line_offset = 31

chip = gpiod.Chip(chip_name)
line = chip.get_line(line_offset)

line.request(consumer="GPIO1_D7_Blink", type=gpiod.LINE_REQ_DIR_OUT)

while True:
    line.set_value(0)
    line.set_value(1)

