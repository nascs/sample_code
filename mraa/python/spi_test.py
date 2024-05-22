#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import mraa
import time

class SPIDevice:
    def __init__(self, spi_index):
        self.spidev = mraa.Spi(spi_index)
        self.freq = 400000

    def initialize(self):
        if self.spidev.frequency(self.freq) != mraa.SUCCESS:
            exit()

        if self.spidev.lsbmode(False) != mraa.SUCCESS:
            exit()

    def write_byte(self, value):
        return self.spidev.writeByte(value)

    def close(self):
        self.close()


if __name__ == '__main__':
    # create spi device
    spi_device = SPIDevice(0)

    # init
    spi_device.initialize()

    try:
        while True:
            # value = ...
            print("0x%x\n" % spi_device.write_byte(0xaa))
            time.sleep(1)
    except:
        print("Error")
    finally:
        spi_device.close()
