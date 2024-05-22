#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import mraa
import time

class Snd:

	def __init__(self, uart_id, baurd_rate, parity, stopbits):
		self.uart_id = uart_id
		self.uart_snd = mraa.Uart(uart_id)
		self.uart_snd.setBaudRate(baurd_rate)
		self.uart_snd.setMode(parity, mraa.UART_PARITY_NONE, stopbits)
		self.uart_snd.setFlowcontrol(False, False)

	def send_message(self, message):
		snd_msg = bytearray(message, "ascii")
		self.uart_snd.write(snd_msg)
		self.uart_snd.flush()

if __name__ == '__main__':
	# init uart
	uart_snd =  Snd(1, 115200, 8, 1)
	
	while True:
		uart_snd.send_message("Hello, this is snd side.\n")
		time.sleep(1)
