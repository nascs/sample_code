#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "mraa/uart.h"

#ifndef FALSE
#define FALSE 0
#define TRUE (!FALSE)
#endif

char *usage =
	"Usage: %s uart_path_id msg\n"
	"Example: %s 4 'this is test message'\n";

int main(int argc, char *argv[]) {
	char usagestr[130];
	char *str = NULL;
	int invalid = 0;
	mraa_uart_context snd_uart;
	mraa_result_t status = MRAA_SUCCESS;

	memset(usagestr, '\0', 130);
	if(argc != 3) {
		snprintf(usagestr, 129, usage, argv[0], argv[0]);
		puts(usagestr);
		return -1;
	}

	mraa_init();

    char uart_path[15];
    snprintf(uart_path, sizeof(uart_path), "/dev/ttyS%d", atoi(argv[1]));
	printf("uart_path: %s, msg: %s\n", uart_path, argv[2]);

	if((snd_uart = mraa_uart_init_raw(uart_path)) == NULL) {
		printf("Failed to initialize UART\n");
		mraa_deinit();
		return -1;
	}

    if ((status = mraa_uart_set_baudrate(snd_uart, 115200)) != MRAA_SUCCESS) {
        return -1;
    }

    if ((status = mraa_uart_set_mode(snd_uart, 8, MRAA_UART_PARITY_NONE, 1)) != MRAA_SUCCESS) {
        return -1;
    }

    if ((status = mraa_uart_set_flowcontrol(snd_uart, FALSE, FALSE)) != MRAA_SUCCESS) {
        return -1;
    }

	while(1) {
		mraa_uart_write(snd_uart, argv[2], strlen(argv[2]));
		sleep(1);
	}

	mraa_uart_stop(snd_uart);
	mraa_deinit();

	return 0;
}
