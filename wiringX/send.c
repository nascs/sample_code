/*
	Copyright (c) 2016 CurlyMo <curlymoo1@gmail.com>

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#include "wiringx.h"

int main(void) {

	struct wiringXSerial_t wiringXSerial = {115200, 7, 'o', 2, 'x'};
	unsigned char data_send = 's';
	int fd = -1;

	if(wiringXSetup("rock4", NULL) == -1) {
		wiringXGC();
		return -1;
	}

	if((fd = wiringXSerialOpen("/dev/ttyS2", wiringXSerial)) < 0) {
		fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
		wiringXGC();
		return -1;
	}

	wiringXSerialPutChar(fd, data_send);

}


