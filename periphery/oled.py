from periphery import I2C
from PIL import Image, ImageDraw, ImageFont
import textwrap
import time

# I2C 地址和设备
I2C_BUS = "/dev/i2c-1"  # 根据你的系统调整
I2C_ADDRESS = 0x3C     # 常用的 OLED 地址

# 初始化 I2C
i2c = I2C(I2C_BUS)

def ssd1306_command(cmd):
    # 发送命令
    msg = I2C.Message([0x00, cmd])
    i2c.transfer(I2C_ADDRESS, [msg])

def initialize_oled():
    # 初始化 OLED 屏幕
    commands = [
        0xAE,  # DISPLAYOFF
        0xD5,  # SETDISPLAYCLOCKDIV
        0x80,  # the suggested ratio 0x80
        0xA8,  # SETMULTIPLEX
        0x3F,
        0xD3,  # SETDISPLAYOFFSET
        0x00,  # no offset
        0x40 | 0x0,  # SETSTARTLINE
        0x8D,  # CHARGEPUMP
        0x14,
        0x20,  # MEMORYMODE
        0x00,  # 0x0 act like ks0108
        0xA1,  # SEGREMAP
        0xC8,  # COMSCANDEC
        0xDA,  # SETCOMPINS
        0x12,
        0x81,  # SETCONTRAST
        0xCF,
        0xD9,  # SETPRECHARGE
        0xF1,
        0xDB,  # SETVCOMDETECT
        0x40,
        0xA4,  # DISPLAYALLON_RESUME
        0xA6,  # NORMALDISPLAY
        0xAF   # DISPLAYON
    ]
    for cmd in commands:
        ssd1306_command(cmd)

def clear_display():
    # 清除显示
    for i in range(8):
        ssd1306_command(0xB0 + i)  # Set page address
        ssd1306_command(0x00)      # Set lower column address
        ssd1306_command(0x10)      # Set higher column address
        for j in range(128):       # 128 columns
            msg = I2C.Message([0x40, 0x00])
            i2c.transfer(I2C_ADDRESS, [msg])

def display_text(text):
    # 使用 Pillow 创建图像
    width = 128
    height = 64
    image = Image.new("1", (width, height))
    draw = ImageDraw.Draw(image)
    font = ImageFont.load_default()

    # 自动换行处理
    lines = textwrap.wrap(text, width=20)  # 20个字符宽度（根据字体和显示屏调整）
    
    y = 0
    for line in lines:
        if y > height - 8:  # 如果超出屏幕高度则停止绘制
            break
        draw.text((0, y), line, font=font, fill=255)
        y += 8  # 每行高度为8像素，可能需要根据字体调整

    # 将图像数据发送到 OLED
    for page in range(8):
        ssd1306_command(0xB0 + page)
        ssd1306_command(0x00)
        ssd1306_command(0x10)
        for col in range(128):
            byte = 0
            for bit in range(8):
                pixel = image.getpixel((col, page * 8 + bit))
                if pixel:
                    byte |= (1 << bit)
            msg = I2C.Message([0x40, byte])
            i2c.transfer(I2C_ADDRESS, [msg])

# 执行初始化和显示
initialize_oled()
clear_display()
display_text("This is a long string that will wrap across multiple lines on the OLED display to demonstrate text wrapping.")
time.sleep(5)
clear_display()

# 关闭 I2C
i2c.close()
