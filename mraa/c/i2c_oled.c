#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "mraa/i2c.h"

#define I2C_BUS 1
#define I2C_ADDR 0x3C

// SSD1306 commands
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

// Initialization commands for SSD1306
const uint8_t init_commands[] = {
	SSD1306_DISPLAYOFF,					// 0xAE
	0x00,								 // Set lower column address
	0x10,								 // Set higher column address
	SSD1306_SETSTARTLINE | 0x00,		  // Set display start line
	0xB0,								 // Set page address
	SSD1306_SETCONTRAST, 0xCF,			// Set contrast control
	0xA1,								 // Set segment remap
	SSD1306_NORMALDISPLAY,				// Normal display
	SSD1306_SETMULTIPLEX, 0x3F,		   // Set multiplex ratio
	0xC8,								 // Set COM output scan direction
	SSD1306_SETDISPLAYOFFSET, 0x00,	   // Set display offset
	SSD1306_SETDISPLAYCLOCKDIV, 0x80,	 // Set display clock divide ratio/oscillator frequency
	SSD1306_SETPRECHARGE, 0xF1,		   // Set pre-charge period
	SSD1306_SETCOMPINS, 0x12,			 // Set COM pins hardware configuration
	SSD1306_SETVCOMDETECT, 0x40,		  // Set VCOMH deselect level
	SSD1306_CHARGEPUMP, 0x14,			 // Enable charge pump regulator
	SSD1306_DISPLAYON					 // Display on
};

// Character map for "Hello Radxa"
typedef struct {
	char ch;
	uint8_t data[6];
} char_map_t;

const char_map_t char_map[] = {
	{'H', {0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F}},
	{'e', {0x00, 0x38, 0x54, 0x54, 0x54, 0x18}},
	{'l', {0x00, 0x00, 0x41, 0x7F, 0x40, 0x00}},
	{'o', {0x00, 0x38, 0x44, 0x44, 0x44, 0x38}},
	{' ', {0x00, 0x00, 0x00, 0x00, 0x00, 0x00}},
	{'R', {0x00, 0x7F, 0x09, 0x19, 0x29, 0x46}},
	{'a', {0x00, 0x20, 0x54, 0x54, 0x54, 0x78}},
	{'d', {0x00, 0x38, 0x44, 0x44, 0x48, 0x7F}},
	{'x', {0x00, 0x44, 0x28, 0x10, 0x28, 0x44}}
};

mraa_i2c_context i2c;

// Function prototypes
void oled_command(uint8_t cmd);
void oled_data(uint8_t data);
void oled_init(void);
void oled_clear(void);
void oled_set_position(uint8_t page, uint8_t column);
void oled_print_char(char ch);
void oled_print_string(const char *str);

void oled_command(uint8_t cmd) {
	uint8_t buf[2] = {0x00, cmd};  // Control byte + command
	mraa_i2c_address(i2c, I2C_ADDR);
	mraa_i2c_write(i2c, buf, 2);
}

void oled_data(uint8_t data) {
	uint8_t buf[2] = {0x40, data};  // Control byte + data
	mraa_i2c_address(i2c, I2C_ADDR);
	mraa_i2c_write(i2c, buf, 2);
}

void oled_init(void) {
	// Send all initialization commands
	for (int i = 0; i < sizeof(init_commands); i++) {
		oled_command(init_commands[i]);
	}
	oled_clear();
}

void oled_clear(void) {
	for (uint8_t page = 0; page < 8; page++) {
		oled_set_position(page, 0);
		for (uint16_t i = 0; i < 128; i++) {
			oled_data(0x00);
		}
	}
}

void oled_set_position(uint8_t page, uint8_t column) {
	oled_command(0xB0 + page);  // Set page address
	oled_command(0x00 + (column & 0x0F));  // Set lower column address
	oled_command(0x10 + ((column >> 4) & 0x0F));  // Set higher column address
}

void oled_print_char(char ch) {
	// Find the character in our character map
	for (size_t i = 0; i < sizeof(char_map) / sizeof(char_map[0]); i++) {
		if (char_map[i].ch == ch) {
			// Send character data
			for (int j = 0; j < 6; j++) {
				oled_data(char_map[i].data[j]);
			}
			// Add space between characters
			oled_data(0x00);
			return;
		}
	}
	// If character not found, print space
	for (int j = 0; j < 7; j++) {
		oled_data(0x00);
	}
}

void oled_print_string(const char *str) {
	while (*str) {
		oled_print_char(*str++);
	}
}

int main() {
	mraa_result_t status = MRAA_SUCCESS;
	
	// Initialize MRAA
	mraa_init();
	
	// Initialize I2C
	i2c = mraa_i2c_init(I2C_BUS);
	if (i2c == NULL) {
		fprintf(stderr, "Failed to initialize I2C\n");
		return 1;
	}
	
	// Initialize the OLED display
	oled_init();
	
	// Set cursor to the beginning of the first line
	oled_set_position(0, 0);
	
	// Print "Hello Radxa" on the OLED
	oled_print_string("Hello Radxa");
	
	// Keep the display on for a while
	sleep(5);
	
	// Clear the display before exiting
	oled_clear();
	
	// Cleanup
	mraa_i2c_stop(i2c);
	mraa_deinit();
	
	return 0;
}
