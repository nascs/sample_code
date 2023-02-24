#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "wiringx.h"
#include "oledfont.h"

#define u8 unsigned char
#define u32 unsigned int
 
#define SlaveAddress 0x3C  //OLED address
#define OLED_CMD  0x00  //OLED address to write
#define OLED_DATA 0x40  //OLED write data
#define SIZE 		16		
#define Max_Column	128		


void OLED_Set_Pos(u8 x, u8 y);
int fd;

//update flash to LCD       
void OLED_Clear(void) {
    u8 i,n;         
    for(i=0;i<8;i++) {  
        wiringXI2CWriteReg8 (fd,OLED_CMD,0xb0+i);    // set page size（0~7）
        wiringXI2CWriteReg8 (fd,OLED_CMD,0x00);      // Set display location column low address
        wiringXI2CWriteReg8 (fd,OLED_CMD,0x10);      // Set display location line low address
        for(n=0;n<128;n++)wiringXI2CWriteReg8(fd,OLED_DATA,0); 
    }   
}

void OLED_Display_On(void) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0X8D);  // SET DCDC
    wiringXI2CWriteReg8(fd,OLED_CMD,0X14);  // DCDC ON
    wiringXI2CWriteReg8(fd,OLED_CMD,0XAF);  // DISPLAY ON
}
  
void OLED_Display_Off(void) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0XAE);  // SET DCDC
    wiringXI2CWriteReg8(fd,OLED_CMD,0X8D);  // DCDC OFF
    wiringXI2CWriteReg8(fd,OLED_CMD,0X10);  // DISPLAY OFF
}

//screen init
int oled_init(void) {
    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringXSetup failed ...\n");
        return -1;
    }
    if((fd = wiringXI2CSetup("/dev/i2c-7",0x3c)) == -1) {
        printf("wiringXI2CSetup failed ...\n");
        return -1;
    }

	wiringXI2CWriteReg8(fd,OLED_CMD,0xAE);  // close display
	wiringXI2CWriteReg8(fd,OLED_CMD,0x00);  // Set the clock frequency division factor and oscillation frequency
	wiringXI2CWriteReg8(fd,OLED_CMD,0x10);  // [3:0], frequency division factor; [7:4], the oscillation frequency
	wiringXI2CWriteReg8(fd,OLED_CMD,0x40);  // Set the number of drive channels
	wiringXI2CWriteReg8(fd,OLED_CMD,0xB0);  // default 0X3F(1/64)

	wiringXI2CWriteReg8(fd,OLED_CMD,0x81);  // default 0
	wiringXI2CWriteReg8(fd,OLED_CMD,0xFF);  // Set the display start line [5:0] and the number of lines.

	wiringXI2CWriteReg8(fd,OLED_CMD,0xA1);
	wiringXI2CWriteReg8(fd,OLED_CMD,0xA6);  // bit2，open/close

	wiringXI2CWriteReg8(fd,OLED_CMD,0xA8);  // mode
	wiringXI2CWriteReg8(fd,OLED_CMD,0x3F);  // [1:0],00, column:01, line:10, page default address 10 ;

	wiringXI2CWriteReg8(fd,OLED_CMD,0xC8);  // Segment redefine Settings ,bit0:0,0->0;1,0->127;

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD3);  // Set the COM scanning direction. bit3:0, normal mode; 1, redefine the mode COM[N-1]->COM0; N: indicates the number of drive routes
	wiringXI2CWriteReg8(fd,OLED_CMD,0x00);  // set com

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD5);  // [5:4]
	wiringXI2CWriteReg8(fd,OLED_CMD,0x80);  // Contrast setting

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD9);  // 1 ~ 255; Default 0X7F (Brightness setting, the larger the brighter)//1~255; Default 0X7F (Brightness setting, the larger the brighter)
	wiringXI2CWriteReg8(fd,OLED_CMD,0xF1);

	wiringXI2CWriteReg8(fd,OLED_CMD,0xDA);
	wiringXI2CWriteReg8(fd,OLED_CMD,0x12);

	wiringXI2CWriteReg8(fd,OLED_CMD,0xDB);  //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc
	wiringXI2CWriteReg8(fd,OLED_CMD,0x40);  // Global display is enabled; Bit 0:1, on; 0, off; (White screen/black screen)

	wiringXI2CWriteReg8(fd,OLED_CMD,0x8D);  // Set the display mode; bit0:1, inverting display; 0: The system displays normally
	wiringXI2CWriteReg8(fd,OLED_CMD,0x14);
	wiringXI2CWriteReg8(fd,OLED_CMD,0xAF);  //get display OLED_Clear();
    OLED_Set_Pos(0,0);
    return 0;
}

// Set the cursor
void OLED_Set_Pos(u8 x, u8 y) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0xB0+y);
    wiringXI2CWriteReg8(fd,OLED_CMD,(x&0x0f));
    wiringXI2CWriteReg8(fd,OLED_CMD,((x&0xf0)>>4)|0x10);
}

// Displays a character, including some characters, at the specified position
//x:0~127
//y:0~63
//mode:0, reverse white display; 1, the system displays normally
//size: Select the font 16/12
void OLED_ShowChar(u8 x,u8 y,u8 chr) {       
  unsigned char c = 0,i=0;
    c =chr - ' ';
	if(x>Max_Column) {
        x = 0;
        y=y+2;
	 }

    if(SIZE == 16) {
        OLED_Set_Pos(x,y); 
        for(i=0;i<8;i++)
        	wiringXI2CWriteReg8(fd,OLED_DATA,F8X16[c*16+i]);
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
	 		wiringXI2CWriteReg8(fd,OLED_DATA,F8X16[c*16+i+8]);
	 } else {
        OLED_Set_Pos(x,y); 

        for(i=0;i<6;i++) {
            wiringXI2CWriteReg8(fd,OLED_DATA,F6x8[c][i]); 
        }
	 }            
}

// m^n
u32 oled_pow(u8 m,u8 n) {
    u32 result=1;    
    while(n--)result*=m;    
    return result;
}


// x,y :start  
// len :length of font
// size:size of font
// mode:mode   0,fill;  1,Superimposed mode
// num:range(0~4294967295);           
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size1) {           
    u8 t,temp;
    u8 enshow=0;                           

 	for(t=0;t<len;t++) {
		temp=(num/oled_pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1)) {
			if(temp==0) {
				OLED_ShowChar(x+(size1/2)*t,y,' ');
				continue;
			} else enshow=1; 
		}
	 	OLED_ShowChar(x+(size1/2)*t,y,temp+'0');
	}
}

// display the char 
void OLED_ShowString(u8 x,u8 y,const u8 *chr) {   
    
    unsigned char j=0;
    while(chr[j] != '\0') {
        OLED_ShowChar(x,y,chr[j]);
		x+=8;
		if(x>=128) {
            x= 0 ;
            y +=2;
		 }
		 j++;
    }
}
int main(void) {
    int ret;
 
    ret = oled_init();
	OLED_Clear();
    if(ret != 0) {
        printf("OLED init error \r\n");
        return -1;
    } 
 
    OLED_ShowString(0,0,"Radxa rock4"); // Change the characters on the screen here

    return 0;
}