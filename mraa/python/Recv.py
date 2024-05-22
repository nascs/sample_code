#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import mraa
import time
import sys

class Recv:
	def __init__(self, uart_id, baurd_rate, parity, stopbits):
		self.uart_id = uart_id
		self.baurd_rate = baurd_rate
		self.parity = parity
		self.stopbits = stopbits
		self.uart = mraa.Uart(uart_id)
		self.initialize_uart()

	def initialize_uart(self):
		self.uart.setBaudRate(self.baurd_rate)
		self.uart.setMode(self.parity, mraa.UART_PARITY_NONE, self.stopbits)
		self.uart.setFlowcontrol(False, False)

	def run(self):
		try:
			while True:
				if self.uart.dataAvailable():
					data_byte = self.uart.readStr(125)
					print(data_byte)

					# Just a two-way half-duplex communication example, "X" is a flag
					if data_byte == "X":
						self.uart.writeStr("Yes, master!")

		except KeyboardInterrupt:
			print("Exiting...")
			self.uart.writeStr("Exiting...")
			self.uart.close()
			sys.exit()

if __name__ == '__main__':

	uart_receiver = Recv(2, 115200, 8, 1)

	uart_receiver.run()
