## env
```
sudo apt-get install cmake build-essential git python3-dev -y
sudo pip3 install smbus2 spidev
git clone https://github.com/nascs/sample_code.git
wiringX: https://wiki.radxa.com/WiringX
```
### LCD 1602/2004 I2C
1. use rsetup to enable i2c7
2. reboot
3. make sure that i2c7 was enabled
 ```bash
 radxa@rock-4c-plus:~$ ls /dev/i2c-*
 /dev/i2c-0  /dev/i2c-7  /dev/i2c-9
 ```
4. pin

   ```bash
   LCD1602         Radxa rock4
    GND             GND
    VCC             5V
    SDA             I2C7_SDA
    SCL             I2C7_SCL
   ```

5. check i2c device and remember  the i2c address 
```bash
radxa@rock-4c-plus:~$ sudo i2cdetect -r -y 7
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- 27 -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --     
```

i2c address:  0x27

6. run program

   ```bash
    sudo python LCD1602.py
   ```

   

7. Check whether the LCD1602/2004 displays the current system time
   Date: 2023/01/06
   Time: 07/19/56

###  adxl345

1. use rsetup to enable i2c7

2. reboot

3. make sure that i2c7 was enabled

   ```bash
   radxa@rock-4c-plus:~$ ls /dev/i2c-*
   /dev/i2c-0  /dev/i2c-7  /dev/i2c-9
   ```

4. pin
   adxl345         Radxa rock4
    GND             GND
    VCC             5V
    SDA             I2C7_SDA
    SCL             I2C7_SCL

5. check i2c device and remember  the i2c address 

   ```bash
   radxa@rock-4c-plus:~$ sudo i2cdetect -r -y 7
        0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
   00:                         -- -- -- -- -- -- -- -- 
   10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
   20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
   30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
   40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
   50: -- -- -- 53 -- -- -- -- -- -- -- -- -- -- -- -- 
   60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
   70: -- -- -- -- -- -- -- -- 
   ```

6. compile  the program adxl345.c /adxl345.cpp, then run the program and check the result

   ```bash
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# gcc adxl345.c -lwiringx
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# ./a.out 
   x: 65519  y: 00055  z: 65298
   x: 65520  y: 00046  z: 65300
   x: 65493  y: 00225  z: 65266
   x: 00141  y: 00340  z: 64836
   x: 65296  y: 65283  z: 00218
   x: 65460  y: 00063  z: 65311
   ```

   ```bash
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# g++ adxl345.cpp -lwiringx
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# sudo ./a.out 
   I2C communication successfully setup.
   x: 0, y: 0, z: 0
   x: 60, y: -126, z: 201
   x: 127, y: -191, z: 281
   x: 129, y: -84, z: 252
   x: -64, y: -62, z: 341
   x: 212, y: 92, z: 174
   x: 172, y: 56, z: 193
   x: 166, y: -55, z: 106
   x: -123, y: -14, z: 37
   x: 99, y: -174, z: 148
   ```

   







###  button + led

1.  pin

      	led					Radxa rock4
      	 s						pin 3
      	 v						3.3v/5v
      	 g						gnd



        button					Radxa rock4
         s						  	pin 5
         v							3.3v/5v  	
         g							gnd

2. compile the program button_led.c

   ```bash
   radxa@rock-4c-plus:~$ gcc button_led.c -lwiringx
   ```

3.  run the program 

   ```bash
   radxa@rock-4c-plus:~$ sudo ./a.out
   ```

4. check the result

   click the button, the led off

### ultrasonic sensor

1. pin

   ```
   ultrasonic sensor				Radxa rock4
   trig							pin 3
   echo 							pin 5
   v								3.3v/5v
   g								gnd
   ```

2. compile the code

   ```bash
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# gcc ultrasonic_sensor.c -lwiringx
   
   ```

3.  run the program and check the result

   ```bash
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# ./a.out 
   57.80 cm
   5.88 cm
   3.67 cm
   7.96 cm
   33.44 cm
   17.12 cm
   5.49 cm
   4.73 cm
   ```



### 4-digit 7-segment Display

1. pin

   ```
   4-digit 7-segment Display				Radxa rock4
   clk 									pin 40
   dio										pin 38
   vcc										3.3v/5v
   gnd										gnd
   ```

2. compile the program and run the program, then check the result

   ```bash
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# gcc tm1637.c -lwiringx
   root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# ./a.out
   ```

   then, you will see "1024" on the module

3. if you want to diaplay other number or letter, you can refer to tm1637.h



### Oled module

1. use rsetup to enable i2c7
2. reboot
3. make sure that i2c7 was enabled

 ```bash
radxa@rock-4c-plus:~$ ls /dev/i2c-*
/dev/i2c-0  /dev/i2c-7  /dev/i2c-9
 ```

4. pin
   LCD1602         Radxa rock4
    GND             GND
    VCC             5V
    SDA             I2C7_SDA
    SCL             I2C7_SCL
5. check i2c device and remember  the i2c address 

```bash
radxa@rock-4c-plus:~$ sudo i2cdetect -r -y 7
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         -- -- -- -- -- -- -- -- 
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
30: -- -- -- -- -- -- -- -- -- -- -- -- 3c -- -- -- 
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
70: -- -- -- -- -- -- -- --     
```

​	i2c address:  0x3c

 6. compile the program and run the program

    ```bash
    root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# gcc oled.c -lwiringx 
    root@rock-4c-plus:/home/radxa/sample_code/modules/keyestudio# ./a.out
    ```

 7.  checkout the result

    you will see "Radxa rock4" on the oled screen, if you want to display the other num or letter(not support chinese yet), you can refer to oledFont.h, 


### buzzer or led
1. pin 

   ```text
   buzzer/led 						Radxa rock4
   s								pin 3
   v								3.3v/5v
   g								gnd
   ```

2. compile the program

   ```bash
   radxa@rock-4c-plus:~ cd sample_code/wiringX
   radxa@rock-4c-plus:~/sample_code/wiringX$ gcc blink.c -lwiringx
   ```

3. run the program and check the result

   ```bash
   radxa@rock-4c-plus:~/sample_code/wiringX$ sudo ./a.out
   ```

   you will see the led blinks once a second, or the buzzer rings once a second



### TCS34725

1. get the source code

   ```bash
   radxa@rock-4c-plus:~$ git clone https://github.com/nascs/TCS34725.git
   radxa@rock-4c-plus:~$ cd TCS34725
   radxa@rock-4c-plus:~/TCS34725$ git checkout -b test origin/test
   ```

2. enable the i2c (take i2c7 for example)

   * use rsetup to enable i2c7

   * reboot

   * make sure that i2c7 was enabled

     ```bash
     radxa@rock-4c-plus:~$ ls /dev/i2c-*
     /dev/i2c-0  /dev/i2c-7  /dev/i2c-9
     ```

   * check i2c device and remember  the i2c address 

     ```bash
     radxa@rock-4c-plus:~$ sudo i2cdetect -r -y 7
          0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
     00:                         -- -- -- -- -- -- -- -- 
     10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
     20: -- -- -- -- -- -- -- -- -- 29 -- -- -- -- -- -- 
     30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
     40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
     50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
     60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
     70: -- -- -- -- -- -- -- --    
     ```

     

3.  pin

   ```bash
   TCS34725         Radxa rock4
    GND             GND
    VCC             5V
    SDA             I2C7_SDA
    SCL             I2C7_SCL
   ```

   

4. run the program and check the result

   ```bash
   radxa@rock-4c-plus:~/TCS34725$ sudo python3 example.py 
   SDL_BM017 initialized
   SDL_BM017 Status= 17
   SDL_BM017 / TCS34725 is present
   ColorList =  [246, 6, 100, 1, 212, 1, 251, 2]
   clear_color=  1782
   red_color=  356
   green_color=  468
   blue_color=  763
   SDL_BM017 Status= 17
   IT set to: 0
   Gain set to: 3
   ColorList =  [255, 255, 255, 255, 255, 255, 255, 255]
   clear_color=  65535
   red_color=  65535
   green_color=  65535
   blue_color=  65535
   SDL_BM017 Status= 17
   SDL_BM017 Status= 17
   Interrupt On
   Interrupt Off
   Interrupt On
   Interrupt Off
   ```



### DS3231 RTC module

Method 1

1.  enable the i2c7
   ```
      please refer to https://wiki.radxa.com/Zero/dev/RTC_module_ds3231
   ```

2. run the program

   ```bash
   radxa@rock-4c-plus:~/sample_code/modules/keyestudio$ sudo  python3 ds3231.py 
   2015/08/12 18:00:00 Wed
   2015/08/12 18:00:01 Wed
   2015/08/12 18:00:02 Wed
   2015/08/12 18:00:03 Wed
   2015/08/12 18:00:04 Wed
   2015/08/12 18:00:05 Wed
   
   ```
   
   or
   
   ```bash
   radxa@rock-4c-plus:~$ echo ds3231 0x68 | sudo tee  /sys/class/i2c-adapter/i2c-7/new_device 
   ds3231 0x68
   
   // read the rtc time
   radxa@rock-4c-plus:~$ sudo hwclock -r 
   2023-02-23 02:57:15.390232+00:00
   
   // Set the system clock to the current time, and then write the system clock into the DS3231 hardware clock
   radxa@rock-4c-plus:~$ sudo date 022310582023
   Thu 23 Feb 2023 10:58:00 AM UTC
   radxa@rock-4c-plus:~$ sudo hwclock -w 
   radxa@rock-4c-plus:~$ date
   Thu 23 Feb 2023 10:58:00 AM UTC
   
   
   //Set the automatic reading time after startup
   radxa@rock-4c-plus:~$ sudo vi /etc/rc.loacl
   
   #! /bin/bash
   echo ds3231 0x68 | sudo tee  /sys/class/i2c-adapter/i2c-
   sudo hwclock -r
   sudo hwclock -s
   
   radxa@rock-4c-plus:~$ sudo chmod 757 /etc/rc.loacl
   
   //  After a few minutes, unplug the network cable and restart the Raspberry PI. Type "date" to check whether the time is correct.
   ```



### DS18B20 

1. use rsetup enable rk3399-w1-gpio4-d6 overlay (titile is "Enable 1-wire on pin 37"), then reboot
2. check whether the /sys/bus/w1/devices/ path exists
3. pin

```bash
ds18b20						Radxa rock4
s							pin 37 (GPIO4_D6)
v							3.3v/5v
g							gnd
```

4. compile the code 

   ```
   radxa@rock-4c-plus:~/sample_code/modules/keyestudio$ gcc ds18b20.c 
   ```

5. run the program and check the result

   ```bash
   radxa@rock-4c-plus:~/sample_code/modules/keyestudio$ sudo ./a.out 
   Open Directory '/sys/bus/w1/devices/' Successfully
   Find file: 28-00000017e18a
   Open file '/sys/bus/w1/devices/28-00000017e18a/w1_slave' fd[3] Successfully
   Read 75B data from file '/sys/bus/w1/devices/28-00000017e18a/w1_slave'
   Temperature is: 28.312 C
   ```

### fan motor

1. pin 

   ```bash
   fan							Radxa rock4
   INA							pin 13
   INB 						pin 14
   VCC							3.3v/5v
   GND							GND
   ```

2. compile the code and run the program

   ```bash
   radxa@rock-4c-plus:~/sample_code/modules/keyestudio$ gcc fan_motor.c -lwiringx
   radxa@rock-4c-plus:~/sample_code/modules/keyestudio$ sudo ./a.out 
   [sudo] password for radxa: 
   INA high
   INA low
   INB high
   INB low
   
   ```





###  IR Receiver

1. replace the default kernel

   ```bash
   //remove the default kernel 
   radxa@rock-4c-plus:~$ sudo dpkg -r linux-headers* linux-image*
   
   radxa@rock-4c-plus:~$ git clone https://github.com/nascs/kernel_packges.git
   radxa@rock-4c-plus:~$ cd kernel_packges/radxa_rock_4/pwm_ir_nec/
   radxa@rock-4c-plus:~/kernel_packages/radxa_rock_4/pwm_ir_nec/$ sudo dpkg -i *.deb && sudo apt-get install -f 
   radxa@rock-4c-plus:~/kernel_packages/radxa_rock_4/pwm_ir_nec/$ sudo update-initramfs -u -k 5.10.110+
   radxa@rock-4c-plus:~/kernel_packages/radxa_rock_4/pwm_ir_nec/$ sudo reboot
   
   // make sure the kernel version is right
   radxa@rock-4c-plus:~$ uname -a
   Linux rock-4c-plus 5.10.110+ #rockchip SMP Wed Mar 8 11:00:03 CST 2023 aarch64 GNU/Linux
   ```

2. test gpio_ir_recv

   ```bash
   radxa@rock-4c-plus:~$ sudo apt-get install evtest -y
   radxa@rock-4c-plus:~$ sudo evtest 
   No device specified, trying to scan all of /dev/input/event*
   Available devices:
   /dev/input/event0:	rk805 pwrkey
   /dev/input/event1:	gpio_ir_recv
   /dev/input/event2:	rockchip-hdmi0 rockchip-hdmi0
   /dev/input/event3:	rockchip-hdmi1 rockchip-hdmi1
   Select the device event number [0-3]: 1
   Input driver version is 1.0.1
   Input device ID: bus 0x19 vendor 0x1 product 0x1 version 0x100
   Input device name: "gpio_ir_recv"
   Supported events:
     Event type 0 (EV_SYN)
     Event type 1 (EV_KEY)
       Event code 2 (KEY_1)
       Event code 3 (KEY_2)
       Event code 4 (KEY_3)
       Event code 5 (KEY_4)
       Event code 6 (KEY_5)
       Event code 7 (KEY_6)
       Event code 8 (KEY_7)
       Event code 9 (KEY_8)
       Event code 10 (KEY_9)
       Event code 11 (KEY_0)
       Event code 13 (KEY_EQUAL)
       Event code 59 (KEY_F1)
       Event code 60 (KEY_F2)
       Event code 114 (KEY_VOLUMEDOWN)
       Event code 115 (KEY_VOLUMEUP)
       Event code 164 (KEY_PLAYPAUSE)
       Event code 363 (KEY_CHANNEL)
       Event code 402 (KEY_CHANNELUP)
       Event code 403 (KEY_CHANNELDOWN)
       Event code 407 (KEY_NEXT)
       Event code 412 (KEY_PREVIOUS)
     Event type 2 (EV_REL)
       Event code 0 (REL_X)
       Event code 1 (REL_Y)
     Event type 4 (EV_MSC)
       Event code 4 (MSC_SCAN)
   Key repeat handling:
     Repeat type 20 (EV_REP)
       Repeat code 0 (REP_DELAY)
         Value    500
       Repeat code 1 (REP_PERIOD)
         Value    125
   Properties:
     Property type 5 (INPUT_PROP_POINTING_STICK)
     /* Please press the infrared remote control */
   Testing ... (interrupt to exit)
   Event: time 1678266663.056227, type 4 (EV_MSC), code 4 (MSC_SCAN), value 00
   Event: time 1678266663.056227, -------------- SYN_REPORT ------------
   Event: time 1678266663.162905, type 4 (EV_MSC), code 4 (MSC_SCAN), value 00
   Event: time 1678266663.162905, -------------- SYN_REPORT ------------
   Event: time 1678266665.032894, type 4 (EV_MSC), code 4 (MSC_SCAN), value 00
   Event: time 1678266665.032894, -------------- SYN_REPORT ------------
   Event: time 1678266665.142902, type 4 (EV_MSC), code 4 (MSC_SCAN), value 00
   Event: time 1678266665.142902, -------------- SYN_REPORT ------------
   Event: time 1678266666.702892, type 4 (EV_MSC), code 4 (MSC_SCAN), value 00
   Event: time 1678266666.702892, -------------- SYN_REPORT ------------
   
   ```

3. env

   ```bash
   radxa@rock-4c-plus:~$ sudo apt-get install build-essential python3-dev lirc liblircclient-dev
   radxa@rock-4c-plus:~$ sudo pip install Cython
   radxa@rock-4c-plus:~$ sudo pip install py-irsend
   radxa@rock-4c-plus:~$ git clone https://github.com/tompreston/python-lirc.git
   radxa@rock-4c-plus:~$ cd python-lirc/
   radxa@rock-4c-plus:~/python-lirc$ python3 setup.py build
   radxa@rock-4c-plus:~/python-lirc$ sudo python3 setup.py install 
   ```

   modify the file  /etc/lirc/lirc_options.conf

   ```bash
   radxa@rock-4c-plus:~$  ls /dev/lirc
   /dev/lirc0
   radxa@rock-4c-plus:~$ sudo vi /etc/lirc/lirc_options.conf
   # These are the default options to lircd, if installed as
   # /etc/lirc/lirc_options.conf. See the lircd(8) and lircmd(8)
   # manpages for info on the different options.
   #
   # Some tools including mode2 and irw uses values such as
   # driver, device, plugindir and loglevel as fallback values
   # in not defined elsewhere.
   
   [lircd]
   nodaemon        = False
   driver          = default
   device          = /dev/lirc0
   output          = /var/run/lirc/lircd
   pidfile         = /var/run/lirc/lircd.pid
   plugindir       = /usr/lib/aarch64-linux-gnu/lirc/plugins
   permission      = 666
   allow-simulate  = No
   repeat-max      = 600
   #effective-user =
   #listen         = [address:]port
   #connect        = host[:port]
   #loglevel       = 6
   #release        = true
   #release_suffix = _EVUP
   #logfile        = ...
   #driver-options = ...
   
   [lircmd]
   uinput          = False
   nodaemon        = False
   
   # [modinit]
   # code = /usr/sbin/modprobe lirc_serial
   # code1 = /usr/bin/setfacl -m g:lirc:rw /dev/uinput
   # code2 = ...
   
   
   # [lircd-uinput]
   # add-release-events = False
   # release-timeout    = 200
   # release-suffix     = _EVUP
   ```

   then reboot the device radxa rock-4c-plus

4. test and test infrared input

   ```bash
   // restart the service 
   radxa@rock-4c-plus:~$  sudo /etc/init.d/lircd stop
   radxa@rock-4c-plus:~$  sudo /etc/init.d/lircd start
   radxa@rock-4c-plus:~$  sudo /etc/init.d/lircd restart
   
   or
   radxa@rock-4c-plus:~$ sudo service lircd stop
   radxa@rock-4c-plus:~$ sudo service lircd start
   radxa@rock-4c-plus:~$ sudo service lircd restart
   
   // test infrared input
   radxa@rock-4c-plus:~$ sudo service lircd stop
   radxa@rock-4c-plus:~$ sudo mode2 -d /dev/lirc0 
   Using driver default on device /dev/lirc0
   Trying device: /dev/lirc0
   Using device: /dev/lirc0
   Running as regular user radxa
   pulse 8998
   space 4394
   pulse 623
   space 483
   pulse 577
   space 546
   pulse 586
   space 523
   pulse 622
   space 488
   pulse 576
   space 464
   pulse 596
   space 493
   space 530
   pulse 21
   space 502
   pulse 595
   pulse 13
   space 592
   space 519
   pulse 21
   pulse 23
   space 1582
   pulse 607
   pulse 10
   space 1604
   pulse 790
   space 1619
   pulse 599
   space 1637
   pulse 565
   space 1646
   pulse 634
   space 1610
   pulse 582
   space 1652
   pulse 556
   space 1657
   pulse 476
   space 656
   space 418
   pulse 11
   pulse 9
   space 511
   space 592
   pulse 13
   space 1694
   pulse 499
   pulse 11
   space 1730
   pulse 612
   space 492
   pulse 608
   space 437
   space 561
   pulse 21
   space 751
   pulse 557
   space 490
   pulse 607
   space 1629
   pulse 593
   space 1642
   pulse 605
   space 502
   pulse 589
   space 522
   pulse 517
   space 1579
   pulse 590
   space 1641
   pulse 563
   space 1645
   pulse 576
   space 1825
   pulse 501
   timeout 129309
   
   Press the remote screen and it should give you a number
   ```

5. record the infrared input and test

   According to the instructions, record the value of the infrared remote control key

   ```
   radxa@rock-4c-plus:~$ irrecord -f -d /dev/lirc0 ~/key_code.lircd.conf
   Using raw access on device /dev/lirc0
   
   irrecord -  application for recording IR-codes for usage with lirc
   Copyright (C) 1998,1999 Christoph Bartelmus(lirc@bartelmus.de)
   
   This program will record the signals from your remote control
   and create a config file for lircd.
   
   A proper config file for lircd is maybe the most vital part of this
   package, so you should invest some time to create a working config
   file. Although I put a good deal of effort in this program it is often
   not possible to automatically recognize all features of a remote
   control. Often short-comings of the receiver hardware make it nearly
   impossible. If you have problems to create a config file READ THE
   DOCUMENTATION at https://sf.net/p/lirc-remotes/wiki
   
   If there already is a remote control of the same brand available at
   http://sf.net/p/lirc-remotes you might want to try using such a
   remote as a template. The config files already contains all
   parameters of the protocol used by remotes of a certain brand and
   knowing these parameters makes the job of this program much
   easier. There are also template files for the most common protocols
   available. Templates can be downloaded using irdb-get(1). You use a
   template file by providing the path of the file as a command line
   parameter.
   
   Please take the time to finish the file as described in
   https://sourceforge.net/p/lirc-remotes/wiki/Checklist/ an send it
   to  <lirc@bartelmus.de> so it can be made available to others.
   
   Press RETURN to continue.
   
   Checking for ambient light  creating too much disturbances.
   Please don't press any buttons, just wait a few seconds...
   
   No significant noise (received 0 bytes)
   
   Enter name of remote (only ascii, no spaces) :key00_encode      
   Using key00_encode.lircd.conf as output filename
   
   Now start pressing buttons on your remote control.
   
   It is very important that you press many different buttons randomly
   and hold them down for approximately one second. Each button should
   generate at least one dot but never more than ten dots of output.
   Don't stop pressing buttons until two lines of dots (2x80) have
   been generated.
   
   Press RETURN now to start recording. /* Press it every second */
   ................................................................................
   
   Please enter the name for the next button (press <ENTER> to finish recording)
   KEY_0
   
   Now hold down button "KEY_0".
   Something went wrong: Signal length is 68
   That's weird because the signal length must be odd!
   Please try again. (28 retries left)
   
   Now hold down button "KEY_0".
   
   Please enter the name for the next button (press <ENTER> to finish recording)
   KEY_9
   
   Now hold down button "KEY_9".
   Something went wrong: Signal length is 0
   That's weird because the signal length must be odd!
   Please try again. (28 retries left)
   
   Now hold down button "KEY_9".
   
   Please enter the name for the next button (press <ENTER> to finish recording)
   
   
   Successfully written config file key00_encode.lircd.conf
   radxa@rock-4c-plus:~$ 
   
   ```

   then there will be a file key00_encode.lircd.conf

   ```bash
   radxa@rock-4c-plus:~$ sudo cp key00_encode.lircd.conf /etc/lirc/lircd.conf.d/
   radxa@rock-4c-plus:~$ cd /etc/lirc/lircd.conf.d/
   radxa@rock-4c-plus:/etc/lirc/lircd.conf.d$ ls
   devinput.lircd.conf  key00_encode.lircd.conf  README.conf.d
   radxa@rock-4c-plus:/etc/lirc/lircd.conf.d$ sudo mv devinput.lircd.conf devinput.lircd.dist
   
   radxa@rock-4c-plus:/etc/lirc/lircd.conf.d$ sudo /etc/init.d/lirc restart
   
   radxa@rock-4c-plus:/etc/lirc/lircd.conf.d$ irw
   0000000000000001 00 KEY_0 key00_encode /* press the keys that have been recorded */
   ```

6.  code with python

   ```bash
   //rename
   radxa@rock-4c-plus:~$ sudo mv /etc/lirc/irexec.lircrc /etc/lirc/lircrc
   
   ```



### IR Transmitter



### knock sensor

1. pin 

   ```bash
   led					Radxa rock4
    s						pin 3
    v						3.3v/5v
    g						gnd
   ```

   ```bash
   knock					Radxa rock4
    s						pin 5
    v						3.3v/5v
    g						gnd
   ```

2. compile the code knock_sensor.c

   ```bash
   gcc knock_sensor -lwiringx -lpthread -o knock
   ```

3.  run the program

   ```bash
   sudo ./knock
   ```

4. checkout the result

   when you knock the sensor,  the led will turn on, after 1 second the led will turn off



### mg90s

1. pin

   ```bash
   ms90s					Radxa rock4
    s						pin 13
    v						3.3v/5v
    g						gnd
   ```

2. compile the code, and run the program

   ```bash
   gcc servo.c -lwiringx
   sudo ./a.out 90		//90 is angle
   ```

3. check the result

   The steering gear will turn at the angle you set.

### ws2812b

1. use rsetup to enable spi1, and make sure spi1 was enabled

   ```bash
   ls /dev/ |grep spi1
   /dev/spi1.0
   ```

2. pin

   ```bash
   ws2812b						Radxa rock4
   IN							spi1 mosi
   GDN							GND
   VCC							VCC
   ```

3. run the program

   ```bash
   sudo python3 ws2812b.py
   ```

   then,  you will see the led blink as the program designed.

4. if you want to change the color of the led, please change the data of led_on in hexadecimal format.

   



### dht11



### dht22



### bluetooth

1. pin 

   ```bash
   HC-06							Radxa rock4
   RXD								UART4_RXD
   TXD								UART4_TXD
   VCC								3.3/5V
   GND								GND
   ```

2. use rsetup to enable uart4 and then reboot,  make sure that uart4 was enabled

   ```bash
   radxa@rock-4c-plus:~$ ls
   /dev/ttyS4
   ```

3. install minicom or the other  graphical serial port tool

   ```minicom
   sudo apt-get install minicom -y
   ```

4. use minicom to open /dev/ttyS4, or you can use sample_code/wiringX/c/recv.c

   ```bash
   sudo minicom -D /dev/ttyS4 -b 9600
   ```

5. pair

   use your computer or phone which installed bluetooth-serial to connect HC06 with bluetooth

6. data transmission

   use your computer or phone to send data to HC06, then you will see data you send in minicom



### Rotation Sensor

1. pin 

   ```bash
   rotation sensor				Radxa rock4
   S								   Pin 26
   VCC								3.3/5V
   GND								GND
   ```

2. run the program

   ```bash
   gcc rotation_sensor.c
   
   sudo ./a.out
   IIO device value: 954
   ```

   and, you can turn the knob and run the program again, then, you will see the different value which ranging from 0 to 1023.

### LM35

