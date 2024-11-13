from periphery import GPIO
from time import sleep

# gpiochip = 4, line = 15
led_gpio = GPIO("/dev/gpiochip4", 15, "out")

while True:
	led_gpio.write(False)
	sleep(1)
	led_gpio.write(True)
	sleep(1)  
