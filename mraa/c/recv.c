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
	"Usage: %s uart_path_id\n"
	"Example: %s 4\n";


int main(int argc, char *argv[]) {
	char usagestr[130];
	char *str = NULL;
	int invalid = 0, uart_id = 0;
	mraa_uart_context recv_uart;
	mraa_result_t status = MRAA_SUCCESS;

	memset(usagestr, '\0', 130);
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
		printf("%s: Invalid GPIO %s\n", argv[0], argv[1]);
		return -1;
	}

	mraa_init();

    char uart_path[15];
    snprintf(uart_path, sizeof(uart_path), "/dev/ttyS%d", atoi(argv[1]));
	printf("uart_path: %s\n", uart_path);

	if((recv_uart = mraa_uart_init_raw(uart_path)) == NULL) {
		printf("Failed to initialize UART\n");
		mraa_deinit();
		return -1;
	}

    if ((status = mraa_uart_set_baudrate(recv_uart, 115200)) != MRAA_SUCCESS) {
        return -1;
    }

    if ((status = mraa_uart_set_mode(recv_uart, 8, MRAA_UART_PARITY_NONE, 1)) != MRAA_SUCCESS) {
        return -1;
    }

    if ((status = mraa_uart_set_flowcontrol(recv_uart, FALSE, FALSE)) != MRAA_SUCCESS) {
        return -1;
    }

    char recv_buff[1024];
    printf("hello\n");
    while(1) {
        if (mraa_uart_data_available(recv_uart, 1) == TRUE) {
            mraa_uart_read(recv_uart, recv_buff, sizeof(recv_buff));
            printf("recv: %s\n", recv_buff);
            sleep(1);
        }
    }
}
