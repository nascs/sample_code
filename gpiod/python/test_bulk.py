#!/usr/bin/env python3
# -*- encoding: utf-8 -*-

import gpiod
from time import sleep
import signal
import sys

gpio_chip_name = '/dev/gpiochip3'
gpio_lines = [4, 5] # GPIO3_A4 GPIO3_A5

chip = gpiod.chip(gpio_chip_name)

for line in gpio_lines:
    line_handle = chip.get_line(line)
    config = gpiod.line_request()
    config.consumer = "my_gpio_example"
    config.request_type = gpiod.line_request.DIRECTION_OUTPUT
    line_handle.request(config)

while True:
    for line in gpio_lines:
        line_handle = chip.get_line(line)
        line_handle.set_value(1)
    sleep(0.5)  # 0.5s

    for line in gpio_lines:
        line_handle = chip.get_line(line)
        line_handle.set_value(0)
    sleep(0.5)  # 0.5s
