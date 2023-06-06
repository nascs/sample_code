import VL53L1X

while True:
   
    tof = VL53L1X.VL53L1X(i2c_bus=3, i2c_address=0x29)
    tof.open()

    # 0 = Unchanged
    # 1 = Short Range (136cm)
    # 2 = Medium Range (290cm)
    # 3 = Long Range (360cm)
    tof.start_ranging(3)  
    distance_in_mm = tof.get_distance()
    tof.stop_ranging()
    print("distance: {}mm".format(distance_in_mm))
   
    distance_in_cm = distance_in_mm/10
    print("distance: {}cm".format(distance_in_cm))
