#!/usr/bin/env python
# -*- encoding: utf-8 -*-

from periphery import PWM
import time

step = 0.05
Range = int(1/0.05)

pwmchip = int(input("pwmchip:"))
channel = int(input("channel:"))

pwm = PWM(pwmchip, channel)

try:
    pwm.frequency = 1e3
    pwm.duty_cycle = 0.00
    pwm.enable()

    while True:
        for i in range(0,Range):
            time.sleep(step)
            pwm.duty_cycle = round(pwm.duty_cycle+step,2)

        if pwm.duty_cycle == 1.5:
            time.sleep(1.5)
        for i in range(0,Range):
            time.sleep(step)
            pwm.duty_cycle = round(pwm.duty_cycle-step,2)
except:
    print("Error !\n")

finally:
    pwm.duty_cycle = 1.0
    pwm.close()
