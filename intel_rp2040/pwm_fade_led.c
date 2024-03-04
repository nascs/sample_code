/**
 * based on https://github.com/raspberrypi/pico-examples/blob/master/pwm/led_fade/pwm_led_fade.c
 */

#include "pico/stdlib.h"
#include <stdio.h>
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h"

#define PWD_FADE_LED_PIN 20

void on_pwm_wrap() {
	static int fade = 0;
	static bool going_up = true;

	pwm_clear_irq(pwm_gpio_to_slice_num(PWD_FADE_LED_PIN));

	if (going_up) {
		++fade;
		if (fade > 255) {
			fade = 255;
			going_up = false;
		}
	} else {
		--fade;
		if (fade < 0) {
			fade = 0;
			going_up = true;
		}
	}

	pwm_set_gpio_level(PWD_FADE_LED_PIN, fade * fade);
}

int main() {

	gpio_set_function(PWD_FADE_LED_PIN, GPIO_FUNC_PWM);

	uint slice_num = pwm_gpio_to_slice_num(PWD_FADE_LED_PIN);

	pwm_clear_irq(slice_num);
	pwm_set_irq_enabled(slice_num, true);
	irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
	irq_set_enabled(PWM_IRQ_WRAP, true);

	pwm_config config = pwm_get_default_config();
	pwm_config_set_clkdiv(&config, 4.f);
	pwm_init(slice_num, &config, true);

	while (1)
		tight_loop_contents();
}
