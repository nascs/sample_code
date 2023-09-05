#include <stdio.h>
#include <gpiod.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 * Take GPIO3_A4 as an example：
 * gpio_chip = 3
 * gpio_line = 4;
*/

int main(int args, char *argv[]) {
	struct gpiod_chip *chip;
	struct gpiod_line *line;
	int ret, chip_num, line_num = 0;
	char *chip_path;
	char *endptr;

	chip_path = (char *)malloc(sizeof(char) * 15);
	chip_path = (char *)memset(chip_path, 0, 15);

	// check the parm acount
	if(args != 3) {
		printf("parameter error\n");
		printf("example:\n    ./a.out 3 4\n");
		return -1;
	}
	// Check the second parm
	chip_num = strtol(argv[1], &endptr, 10);
    if (*endptr != '\0') {
        printf("parm 1: type error\n");
        return -1;
    }
	// Check the third parm
	line_num = strtol(argv[2], &endptr, 10);
    if (*endptr != '\0') {
        printf("parm 2: type error\n");
        return -1;
    }

	sprintf(chip_path, "/dev/gpiochip%s", argv[1]);

	// Open the GPIO chip
	chip = gpiod_chip_open(chip_path);
	if(chip == NULL) {
		printf("open error !\n");
		return -1;
	}

	line = gpiod_chip_get_line(chip, line_num);
	if(line == NULL) {
		printf("open error !\n");
		return -1;
	}

	// Set the line to output mode, and set the default logic value
	if((ret = gpiod_line_request_output(line, "led_out_high", 0)) < 0) {
		printf("set direction error !\n");
		return -1;
	}

	for(int i = 0; i < 10; i++) {
 		// Set the line to 1
 		gpiod_line_set_value(line, 1);
		// sleep 1s
		sleep(1);
		// Set the line to 0
		gpiod_line_set_value(line, 0);
		// sleep 1s
		sleep(1);
	}

	gpiod_line_release(line);
	gpiod_chip_close(chip);

	return 0;
}