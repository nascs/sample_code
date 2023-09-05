#include <stdio.h>
#include <gpiod.h>

#ifndef	CONSUMER
#define	CONSUMER	"Consumer"
#endif

/*
 * Take GPIO3_A4 as an example：
 * gpio_chip = 3
 * gpio_line = 4;
*/

int main() {
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int i, line_value;

	chip = gpiod_chip_open_by_name("gpiochip3");
	if(chip == NULL) {
		printf("Failed to open chip\n");
		return -1;
	}

	line = gpiod_chip_get_line(chip, 4);
	if(line == NULL) {
		printf("Faile to get line\n");
		return -1;
	}

	// Set line to be an input
	if((gpiod_line_request_input(line, CONSUMER)) <0) {
		printf("Failed to set line as input\n");
		return -1;
	}

	for(i = 0; i < 30; i++) {
		line_value = gpiod_line_get_value(line);
		if(line_value < 0) {
			printf("Failed to get line value\n");
			return -1;
		}
		printf("line value: %d\n", line_value);
		sleep(1);
	}

	gpiod_line_release(line);
	gpiod_chip_close(chip);

	return 0;
}