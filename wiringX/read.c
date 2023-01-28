/*
	Copyright (c) 2016 CurlyMo <curlymoo1@gmail.com>

  This Source Code Form is subject to the terms of the Mozilla Public
  License, v. 2.0. If a copy of the MPL was not distributed with this
  file, You can obtain one at http://mozilla.org/MPL/2.0/.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "wiringx.h"

#define gpio 8

int main(int argc, char *argv[]) {

	if(wiringXSetup("rock4", NULL) == -1) {
		wiringXGC();
		return -1;
	}
	pinMode(gpio, PINMODE_INPUT);

	while(1) {
		printf("Reading from GPIO %d: value is %d\n", gpio, digitalRead(gpio));
		sleep(1);
	}

	return 0;
}
