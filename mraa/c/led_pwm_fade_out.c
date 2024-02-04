#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "mraa/pwm.h"

/* PWM period in us */
#define PWM_FREQ 1e3

char *usage =
	"Usage: %s pwm_pin\n"
	"Example: %s 3\n";

int main(int argc, char *argv[]) {
	char usagestr[130];
	char *str = NULL;
	int invalid = 0, pwm_num = 0;
	mraa_result_t status = MRAA_SUCCESS;
	mraa_pwm_context pwm;
	float output = 0.0;
	float duty_cycle = 0.0;
	float step = 0.05;

	memset(usagestr, '\0', 130);
	// expect only 1 argument => argc must be 2
	if(argc != 2) {
		snprintf(usagestr, 129, usage, argv[0], argv[0]);
		puts(usagestr);
		return -1;
	}
	// check for a valid, numeric argument
	str = argv[1];
	while(*str != '\0') {
		if(!isdigit(*str)) {
			invalid = 1;
		}
		str++;
	}
	if(invalid == 1) {
		printf("%s: Invalid GPIO %s\n", argv[0], argv[2]);
		return -1;
	}
	pwm_num = atoi(argv[1]);

	mraa_init();

	/* init pwm */
	if((pwm = mraa_pwm_init(pwm_num)) == NULL) {
		printf("Failed to initialize PWM\n");
		mraa_deinit();
		return -1;
	}
	/* set period */
	if((status = mraa_pwm_period_us(pwm, PWM_FREQ))) {
		printf("Faile to set pwm period\n");
		return -1;
	}
	/* enable pwm */
	if((status = mraa_pwm_enable(pwm, 1)) != MRAA_SUCCESS) {
		printf("Faile to Enable PWM\n");
		return -1;
	}

	while (1) {
		// Set pwm duty cycle
		mraa_pwm_write(pwm, duty_cycle);

		// sleep 100 ms
		usleep(100000);

		// change the duty cycle
		duty_cycle += step;
		if (duty_cycle > 1.0) {
			duty_cycle = 0.0;
		}

		printf("PWM value: %f\n", mraa_pwm_read(pwm));
	}

	mraa_pwm_close(pwm);

	return 0;
}
