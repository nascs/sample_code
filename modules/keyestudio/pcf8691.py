#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import smbus2

bus = smbus2.SMBus(8)
address = 0x48

# 读取 ADC 的数值
def read_adc(channel):
    bus.write_byte(address, channel)
    value = bus.read_byte(address)
    return value

# 写入 DAC 的数值
def write_dac(value):
    bus.write_byte_data(address, 0x40, value)

# 示例：读取 ADC 通道 0 的数值并打印
adc_value = read_adc(0)
print("ADC Value: ", adc_value)