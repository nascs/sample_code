from periphery import I2C
import time

I2C_ADDR = 0x3c
I2C_BUS = "/dev/i2c-8"

i2c = I2C(I2C_BUS)

# SSD1306 init_cmds
init_cmds = [
    0xAE,  # Display off
    0x00,  # Set lower column address
    0x10,  # Set higher column address
    0x40,  # Set display start line
    0xB0,  # Set page address
    0x81,  # Set contrast control
    0xCF,
    0xA1,  # Set segment remap
    0xA6,  # Normal display
    0xA8,  # Set multiplex ratio
    0x3F,
    0xC8,  # Set COM output scan direction
    0xD3,  # Set display offset
    0x00,
    0xD5,  # Set display clock divide ratio/oscillator frequency
    0x80,
    0xD9,  # Set pre-charge period
    0xF1,
    0xDA,  # Set COM pins hardware configuration
    0x12,
    0xDB,  # Set VCOMH deselect level
    0x40,
    0x8D,  # Enable charge pump regulator
    0x14,
    0xAF   # Display on
]

for cmd in init_cmds:
    i2c.transfer(I2C_ADDR, [I2C.Message([0x00, cmd])])

def oled_clear():
    for page in range(8):
        i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0xB0 + page])])
        i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0x00])])
        i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0x10])])
        for _ in range(128):
            i2c.transfer(I2C_ADDR, [I2C.Message([0x40, 0x00])])

char_map = {
    "H": [0x00, 0x7F, 0x08, 0x08, 0x08, 0x7F,],
    "R": [0x00, 0x7F, 0x09, 0x19, 0x29, 0x46],
    "e": [0x00, 0x38, 0x54, 0x54, 0x54, 0x18],
    "l": [0x00, 0x00, 0x41, 0x7F, 0x40, 0x00],
    "o": [0x00, 0x38, 0x44, 0x44, 0x44, 0x38],
    "r": [0x00, 0x7C, 0x08, 0x04, 0x04, 0x08],
    "a": [0x00, 0x20, 0x54, 0x54, 0x54, 0x78],
    "d": [0x00, 0x38, 0x44, 0x44, 0x48, 0x7F],
    "x": [0x00, 0x44, 0x28, 0x10, 0x28, 0x44]
}

def string_to_bytes(string):
    bytes_list = []
    for char in string:
        bytes_list.extend(char_map.get(char, [0x00] * 4))
        bytes_list.append(0x00)
    return bytes_list

oled_clear()
hello_world_bytes = string_to_bytes("Hello Radxa")
i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0xB0])])
i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0x00])])
i2c.transfer(I2C_ADDR, [I2C.Message([0x00, 0x10])])
for byte in hello_world_bytes:
    i2c.transfer(I2C_ADDR, [I2C.Message([0x40, byte])])

i2c.close()
