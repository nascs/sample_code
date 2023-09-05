#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/syscall.h>

#include "wiringx.h"



void *interrupt(void *gpio_void_ptr) {
	int i = 0;
	int gpio = *(int *)gpio_void_ptr;

	while(++i < 20) {
		if(waitForInterrupt(gpio, 1000) > 0) {
			printf(">>Interrupt on GPIO %d, and led on\n", gpio);
		} else {
			printf("  Timeout on GPIO %d, and led off\n", gpio);
		}
	}
}

int main(int argc, char *argv[]) {
	pthread_t pth;
	int led = 8, knock = 9;
	int i = 0, err = 0;
	int status = 0;

	if(wiringXSetup("rock4", NULL) == -1) {
		wiringXGC();
		return -1;
	}

	pinMode(led, PINMODE_OUTPUT);
	// pinMode(knock, PINMODE_INPUT);
	if((wiringXISR(knock, ISR_MODE_FALLING)) != 0) {
		printf("%s: Cannot set GPIO %d to interrupt BOTH\n", argv[0], knock);
		wiringXGC();
		return -1;
	}

	err = pthread_create(&pth, NULL, interrupt, &knock);
	if(err != 0) {
		printf("Can't create thread: [%s]\n", strerror(err));
		wiringXGC();
		return -1;
	} else {
		printf("Thread created succesfully\n");
	}

	while(1) {
		if(waitForInterrupt(knock, 1000) == 0) {
			digitalWrite(led, LOW);
		} else {
			digitalWrite(led, HIGH);
		}
		sleep(1);
	}

	printf("Main finished, waiting for thread ...\n");
	pthread_join(pth, NULL);
	wiringXGC();

	return 0;
}
