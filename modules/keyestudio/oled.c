#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "wiringx.h"
#include "oledfont.h"

#define u8 unsigned char
#define u32 unsigned int
 
#define SlaveAddress 0x3C  //OLED地址
#define OLED_CMD  0x00  //OLED写命令
#define OLED_DATA 0x40  //OLED写数据
#define SIZE 		16		//字符大小
#define Max_Column	128		//最大列数


void OLED_Set_Pos(u8 x, u8 y);
int fd;

//更新显存到LCD       
void OLED_Clear(void) {
    u8 i,n;         
    for(i=0;i<8;i++) {  
        wiringXI2CWriteReg8 (fd,OLED_CMD,0xb0+i);    //设置页地址（0~7）
        wiringXI2CWriteReg8 (fd,OLED_CMD,0x00);      //设置显示位置—列低地址
        wiringXI2CWriteReg8 (fd,OLED_CMD,0x10);      //设置显示位置—列高地址   
        for(n=0;n<128;n++)wiringXI2CWriteReg8(fd,OLED_DATA,0); 
    }   
}
//开启OLED显示    
void OLED_Display_On(void) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0X8D);  //SET DCDC命令
    wiringXI2CWriteReg8(fd,OLED_CMD,0X14);  //DCDC ON
    wiringXI2CWriteReg8(fd,OLED_CMD,0XAF);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0XAE);  //SET DCDC命令
    wiringXI2CWriteReg8(fd,OLED_CMD,0X8D);  //DCDC OFF
    wiringXI2CWriteReg8(fd,OLED_CMD,0X10);  //DISPLAY OFF
}

//屏幕初始化函数
int oled_init(void) {
    if(wiringXSetup("rock4", NULL) == -1) {
        printf("wiringXSetup failed ...\n");
        return -1;
    }
    if((fd = wiringXI2CSetup("/dev/i2c-7",0x3c)) == -1) {
        printf("wiringXI2CSetup failed ...\n");
        return -1;
    }

	wiringXI2CWriteReg8(fd,OLED_CMD,0xAE);  //关闭显示
	wiringXI2CWriteReg8(fd,OLED_CMD,0x00);  //设置时钟分频因子,震荡频率
	wiringXI2CWriteReg8(fd,OLED_CMD,0x10);  //[3:0],分频因子;[7:4],震荡频率
	wiringXI2CWriteReg8(fd,OLED_CMD,0x40);  //设置驱动路数
	wiringXI2CWriteReg8(fd,OLED_CMD,0xB0);  //默认0X3F(1/64)

	wiringXI2CWriteReg8(fd,OLED_CMD,0x81);  //默认为0
	wiringXI2CWriteReg8(fd,OLED_CMD,0xFF);  //设置显示开始行 [5:0],行数.

	wiringXI2CWriteReg8(fd,OLED_CMD,0xA1);  //电荷泵设置
	wiringXI2CWriteReg8(fd,OLED_CMD,0xA6);  //bit2，开启/关闭

	wiringXI2CWriteReg8(fd,OLED_CMD,0xA8);  //设置内存地址模式 
	wiringXI2CWriteReg8(fd,OLED_CMD,0x3F);  //[1:0],00，列地址模式;01，行地址模式;10,页地址模式;默认10;

	wiringXI2CWriteReg8(fd,OLED_CMD,0xC8);  //段重定义设置,bit0:0,0->0;1,0->127;

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD3);  //设置COM扫描方向;bit3:0,普通模式;1,重定义模式 COM[N-1]->COM0;N:驱动路数 
	wiringXI2CWriteReg8(fd,OLED_CMD,0x00);  //设置COM硬件引脚配置

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD5);  //[5:4]配置
	wiringXI2CWriteReg8(fd,OLED_CMD,0x80);  //对比度设置

	wiringXI2CWriteReg8(fd,OLED_CMD,0xD9);  //1~255;默认0X7F (亮度设置,越大越亮)
	wiringXI2CWriteReg8(fd,OLED_CMD,0xF1);  //设置预充电周期

	wiringXI2CWriteReg8(fd,OLED_CMD,0xDA);  //[3:0],PHASE 1;[7:4],PHASE 2;
	wiringXI2CWriteReg8(fd,OLED_CMD,0x12);  //设置VCOMH 电压倍率

	wiringXI2CWriteReg8(fd,OLED_CMD,0xDB);  //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc
	wiringXI2CWriteReg8(fd,OLED_CMD,0x40);  //全局显示开启;bit0:1,开启;0,关闭;(白屏/黑屏)

	wiringXI2CWriteReg8(fd,OLED_CMD,0x8D);  //设置显示方式;bit0:1,反相显示;0,正常显示
	wiringXI2CWriteReg8(fd,OLED_CMD,0x14);  //开启显示 
	wiringXI2CWriteReg8(fd,OLED_CMD,0xAF);  //开启显示 OLED_Clear();
    OLED_Set_Pos(0,0);
    return 0;
}
//设置光标
void OLED_Set_Pos(u8 x, u8 y) {
    wiringXI2CWriteReg8(fd,OLED_CMD,0xB0+y);
    wiringXI2CWriteReg8(fd,OLED_CMD,(x&0x0f));
    wiringXI2CWriteReg8(fd,OLED_CMD,((x&0xf0)>>4)|0x10);
}
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//mode:0,反白显示;1,正常显示                 
//size:选择字体 16/12 
void OLED_ShowChar(u8 x,u8 y,u8 chr) {       
  unsigned char c = 0,i=0;
    c =chr - ' '; //»ñÈ¡×Ö·ûµÄÆ«ÒÆÁ
	if(x>Max_Column) {
        x = 0;  //Èç¹ûÁÐ³öÁË·¶Î§£¬¾Í´ÓÏÂÁ½Ò³µÄµÚ0ÁÐ¿ªÊ¼
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

//m^n函数
u32 oled_pow(u8 m,u8 n) {
    u32 result=1;    
    while(n--)result*=m;    
    return result;
}
//显示2个数字
//x,y :起点坐标  
//len :数字的位数
//size:字体大小
//mode:模式   0,填充模式;1,叠加模式
//num:数值(0~4294967295);           
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

//显示字符串
//x,y:起点坐标  
//size:字体大小 
//*p:字符串起始地址 
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
 
    OLED_ShowString(0,0,"Radxa rock4"); //这里改屏幕显示的字符

    return 0;
}