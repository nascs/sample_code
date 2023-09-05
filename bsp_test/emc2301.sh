#!/bin/bash
#
# Jeff Geerling's super-rudimentary fan controller script for the CM4.
#
# Use:
#   1. Download this script to a path like `/opt/cm4-fan.sh`
#   2. Run it with: `nohup bash /opt/cm4-fan.sh`
#   3. Profit!
#
# You should wrap it in a systemd unit file if you want it to persist and come
# up after reboot, too.

# Explicitly set $PATH so i2c tools are found.
#PATH=$PATH:/usr/sbin

# Temperature set point (Celcius).
TEMP_THRESHOLD=48
TEMP_COMPARE=$(($TEMP_THRESHOLD * 1000))

# Minimum fan speed (0-255).
MIN_FAN_SPEED=100
MIN_FAN_SPEED_HEX=$(printf "0x%02x" "$MIN_FAN_SPEED")

# Maximum fan speed (0-255).
MAX_FAN_SPEED=255
MAX_FAN_SPEED_HEX=$(printf "0x%02x" "$MAX_FAN_SPEED")

# TODO: The script should also check that `i2cget` is present, and that the
# fan is visible on the bus.

# Start a loop.
while true; do
	# Get the current temperature.
	CURRENT_TEMP=$(cat /sys/class/thermal/thermal_zone0/temp)
	if [ $CURRENT_TEMP -ge $TEMP_COMPARE ]; then
		# If current temperature is more than desired, set fan to maximum speed.
		i2cset -y 0 0x2f 0x30 $MAX_FAN_SPEED_HEX
	else
		# If current temperature is good, set fan to minimum speed.
		i2cset -y 0 0x2f 0x30 $MIN_FAN_SPEED_HEX
	fi
	sleep 10
done
