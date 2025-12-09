#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include "hardware/clocks.h" // 需要引入 clocks

// UART settings
#define UART_ID uart0
#define BAUD_RATE 115200
#define DATA_BITS 8
#define STOP_BITS 1
#define PARITY	UART_PARITY_NONE
#define UART_TX_PIN 0
#define UART_RX_PIN 1

#define FAN_PIN 21
#define LOW_FREQ 100 // 降低到 100Hz

// temperature_buffer for incoming data
#define BUF_SIZE 256
char temperature_buffer[BUF_SIZE];
int buf_index = 0;

#define ADC_PIN 26
#define R_FIXED 10000.0f //10KΩ
#define ADC_MAX 4095.0f // 12 bit ADC max value

void set_pwm_duty_cycle(uint gpio, float duty_percent) {
    if (duty_percent < 0.0f) duty_percent = 0.0f;
    if (duty_percent > 100.0f) duty_percent = 100.0f;
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    uint32_t wrap_value = pwm_hw->slice[slice_num].top;
    uint16_t level = (uint16_t)((duty_percent / 100.0f) * (wrap_value + 1));
    pwm_set_gpio_level(gpio, level);
}

void pwm_init_fan(uint gpio, uint32_t freq_hz) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    
    // 计算 125MHz 下的参数
    // For simplicity, fixed frequency allocation is used for low-frequency we use 50.0
    float div = 50.0f; 
    uint32_t clock_hz = 125000000;
    uint32_t wrap = (clock_hz / (freq_hz * div)) - 1;

    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_clkdiv(&config, div);
    pwm_init(slice_num, &config, true);
    
    printf("PWM Initialized: %d Hz\n", freq_hz);
}

int main() {

	// Initialize stdio
	stdio_init_all();

	// Initialize UART
	uart_init(UART_ID, BAUD_RATE);
	gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
	gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);
	uart_set_hw_flow(UART_ID, false, false);
	uart_set_format(UART_ID, DATA_BITS, STOP_BITS, PARITY);
	uart_set_fifo_enabled(UART_ID, false);

	// Initialize ADC
	adc_init();
	adc_gpio_init(26);
	adc_select_input(0);

	// Initialize fan
	pwm_init_fan(FAN_PIN, LOW_FREQ);

	// Send a test message
	printf("UART echo example, Sending test message...\n");
	uart_puts(UART_ID, "Hello, UART!\n");

	while (1) {
		temperature_buffer[buf_index] = '\0';  // Null-terminate the string
		uint16_t adc_value = adc_read();
		float r_thermistor;
		 if(adc_value >= ADC_MAX) {
			printf("adc_value is INFINITY\n");
		 } else if (adc_value <= 0) {
			printf("adc_value is 0\n");
		 } else {
			r_thermistor = R_FIXED * (adc_value / (ADC_MAX - adc_value));
			printf("adc_value: %d, r_thermistor: %f\n", adc_value, r_thermistor);
			// printf("==> adc_value: %d, r_thermistor: %f, RECV: %s <==\n", adc_value, r_thermistor, temperature_buffer);

			if(r_thermistor >= 3741.6 && r_thermistor <= 4869.3) {
				// 50°C ～ 60°C：r_thermistor: 3741.6 ~ 4869.3
				printf("(50°C, 60°C]\r\n");
				set_pwm_duty_cycle(FAN_PIN, 60.0f);
			} else if(r_thermistor >= 3000.0 && r_thermistor <= 3976.1) {
				// 60°C ～ 70°C：r_thermistor: 3000.0 ~ 3976.1
				printf("(60°C, 70°C]\r\n");
				set_pwm_duty_cycle(FAN_PIN, 70.0f);
			} else if(r_thermistor >= 2234.8 && r_thermistor <= 3737.0) {
				// 70°C ～ 80°C：r_thermistor: 2234.8 ~ 3737.0
				printf("(70°C, 80°C]\r\n");
				set_pwm_duty_cycle(FAN_PIN, 80.0f);
			} else if(r_thermistor < 2234.8) {
				// 80°C ～ 90°C：r_thermistor: 1914.5 ~ 2234.8
				printf("(80°C, 100°C]\r\n");
				set_pwm_duty_cycle(FAN_PIN, 90.0f);
			} else {
				printf("fan stop \r\n");
			}
		 }
		buf_index = 0;  // Reset temperature_buffer index
		sleep_ms(1000);
	}

	return 0;
}
