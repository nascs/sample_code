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

char *usage =
	"Usage: %s platform GPIO \n"
	"       GPIO to read from = input\n"
	"Example: %s rock3a_v1_3 4 \n";

int main(int argc, char *argv[]) {
	char *str = NULL, *platform = NULL;
	char usagestr[170];
	int i = 0, gpio = 0, invalid = 0;

	memset(usagestr, '\0', 170);

	// expect 2 arguments => argc must be 3
	if(argc != 3) {
		snprintf(usagestr, 169, usage, argv[0], argv[0]);
		puts(usagestr);
		return -1;
	}

	// check for valid, numeric arguments
	for(i=2; i<argc; i++) {
		str = argv[i];
		while(*str != '\0') {
			if(!isdigit(*str)) {
				invalid = 1;
			}
			str++;
		}
		if(invalid == 1) {
			printf("%s: Invalid GPIO %s\n", argv[0], argv[i]);
			return -1;
		}
	}

	platform = argv[1];
	gpio = atoi(argv[2]);

	if(wiringXSetup(platform, NULL) == -1) {
		wiringXGC();
		return -1;
	}

	if(wiringXValidGPIO(gpio) != 0) {
		printf("%s: Invalid GPIO %d for input\n", argv[0], gpio);
		wiringXGC();
		return -1;
	}

	pinMode(gpio, PINMODE_INPUT);

	while(1) {
		printf("Reading from GPIO %d: %d\n", gpio, digitalRead(gpio));
		sleep(1);
		printf("Reading from GPIO %d: %d\n", gpio, digitalRead(gpio));
		sleep(1);
	}

	return 0;
}
