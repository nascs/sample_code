#!/usr/bin/env python
# -*- encoding: utf-8 -*-

#!/usr/bin/env python
# -*- encoding: utf-8 -*-

import OPi.GPIO as GPIO
from mfrc522 import SimpleMFRC522
import time

rfid_rc522 = SimpleMFRC522()
data = "0x110101001"

rfid_rc522.write(data)

print("write ok")
