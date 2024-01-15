#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa/pwm.h"

/* Radxa ROCK 5A Pin 11 */
#define PWM 11

/* PWM period in us */
#define PWM_FREQ 1e3

int main() {
	mraa_result_t status = MRAA_SUCCESS;
	mraa_pwm_context pwm;
	float output = 0.0;
	float duty_cycle = 0.0;
	float step = 0.05;

	mraa_init();

	/* init pwm */
	if((pwm = mraa_pwm_init(PWM)) == NULL) {
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
		// 设置 PWM 占空比
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
