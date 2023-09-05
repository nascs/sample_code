/*
  Copyright (c) 2023 Radxa Ltd.
  Author: Nascs <nascs@radxa.com>
  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdio.h>
#include <unistd.h>
#include "wiringx.h"

int main() {

	int fd ;
	
	if(wiringXSetup("rock4", NULL) == -1) {
		printf("wiringXSetup failed ...\n");
		return -1;
	}
	if((fd = wiringXI2CSetup("/dev/i2c-7",0x20)) == -1) {
		printf("wiringXI2CSetup failed ...\n");
		return -1;
	}
	
	while(1) {
		wiringXI2CWrite(fd,0x5f);
		sleep(1);
		wiringXI2CWrite(fd,0x7f);
		sleep(1);
	}


	return 0;
}
