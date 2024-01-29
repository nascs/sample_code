#include "mraa.h"
#include <stdio.h>

#define PIN 28

volatile int cnt = 0;

void interrupt_handle(void *arg) {
	printf(">> This is interrupt handle function !\n");
	cnt++;
}

int main() {
	mraa_gpio_context pin;
	mraa_result_t status = MRAA_SUCCESS;

	mraa_init();

	if((pin = mraa_gpio_init(PIN)) == NULL) {
		printf("Failed to initialize GPIO\n");
		mraa_deinit();
		return -1;
	}

	/* configure as input */
	if((status = mraa_gpio_dir(pin, MRAA_GPIO_IN)) != MRAA_SUCCESS) {
		printf("Failed to set direction !\n");
		return -1;
	}

	if((status = mraa_gpio_isr(pin, MRAA_GPIO_EDGE_FALLING, interrupt_handle, NULL)) != MRAA_SUCCESS) {
		printf("Failed to trigger interrupt !\n");
		return -1;
	}

	sleep(10);

	printf("cnt = %d\n", cnt);

	mraa_gpio_isr_exit(pin);

	mraa_gpio_close(pin);

	return(0);
}
