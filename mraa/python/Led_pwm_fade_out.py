#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import mraa
import time

class Led_pwm_fade_out:
    def __init__(self, pwm_pin):
        self.pwm_pin = pwm_pin
        self.pwm = mraa.Pwm(pwm_pin)
        self.duty_cycle = 0.0
        self.pwm_freq = 1e3
        self.pwm_step = 0.05

    def initialize(self):
        if self.pwm == None:
            exit()

        if self.pwm.period_us(self.pwm_freq) != mraa.SUCCESS:
            mraa.Pwm.close()
            exit()

        if self.pwm.enable(True) != mraa.SUCCESS:
            mraa.Pwm.close()
            exit()

    def set_duty_cycle(self, duty_cycle):
        self.duty_cycle = duty_cycle
        self.pwm.write(duty_cycle)

    def run(self):
        try:
            while True:
                self.set_duty_cycle(self.duty_cycle)
                self.duty_cycle += self.pwm_step
                if self.duty_cycle > 1.0:
                    self.duty_cycle = 0.0
                print("0x%x\n" %self.pwm.read(self.pwm))
                time.sleep(1)

        except:
            print("Error")

        finally:
            self.pwm.write(0)  # Stop PWM
            self.pwm.disable()  # Disable PWM
            self.pwm.close()  # Close PWM

if __name__ == '__main__':

    pwm_controller = Led_pwm_fade_out(28)

    pwm_controller.initialize()

    pwm_controller.run()
