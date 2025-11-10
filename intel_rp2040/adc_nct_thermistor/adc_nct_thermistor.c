#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

#define NTC_RESISTOR 10000.0f // 10k ohm resistor
#define ADC_MAX 4095.0f   // 12-bit ADC

int main() {
	stdio_init_all();
	adc_init();
	adc_gpio_init(26); // Initialize GP26 for ADC input (ADC0)
	

	while (1) {
		adc_select_input(0); // Select ADC channel 0 (GP26)
		uint16_t adc_value = adc_read() >> 4; // Read ADC value

		if(adc_value > ADC_MAX) {
			printf("ADC value out of range, this is infinite, indicating an open circuit\n");
		} else if(adc_value <= 0) {
			printf("ADC value is zero, indicating a short circuit\n");
		} else {
			// Calculate thermistor resistance using voltage divider formula

			float r_thermistor = NTC_RESISTOR * (adc_value / (ADC_MAX - adc_value));

			// Output the resistance value
			printf("ADC Value: %d, Thermistor Resistance: %.2f ohms\n", adc_value, r_thermistor);
		}

		sleep_ms(1000); // Wait for 1 second before next reading

	}


}
