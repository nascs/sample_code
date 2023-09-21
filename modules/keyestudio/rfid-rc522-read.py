#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import OPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
import time

reader = SimpleMFRC522()

try:
    while True:
        print("请将卡片放置在读卡器上...")
        id, text = reader.read()
        print("卡片 UID: {}".format(id))
        print("卡片内容: {}".format(text))
        time.sleep(2)
finally:
    GPIO.cleanup()
