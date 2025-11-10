#include "pico/stdlib.h"

int main() {
	int gpios[] = {28,29,4,5,6,3,11,8,10,16,7,12,13,15,14,25,2,26,19,17,18,9,24,27,22,23,21,20};
	int i = 0;

	for(i = 0; i < sizeof(gpios)/sizeof(gpios[0]); i++) {
		gpio_init(gpios[i]);
		gpio_set_dir(gpios[i], GPIO_OUT);
	}

	while(1) {
		for(i = 0; i < (sizeof(gpios)/sizeof(gpios[0])); i++) {
			gpio_put(gpios[i], 1);
		}
		sleep_ms(250); // 延时250ms
		for(i = 0; i < (sizeof(gpios)/sizeof(gpios[0])); i++) {
			gpio_put(gpios[i], 0);
		}
		sleep_ms(250);
	}

	return 0;
}
