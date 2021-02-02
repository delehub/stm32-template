#include "sys.h"

#ifndef _SOFTSPI_H_
#define _SOFTSPI_H_




//本测试程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
/******************************************************************************
接口定义在lcd.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口
#define LCD_LED        	GPIO_Pin_9  //PB9 连接至TFT -LED
#define LCD_RS         	GPIO_Pin_10	//PB10连接至TFT --RS
#define LCD_CS        	GPIO_Pin_11 //PB11 连接至TFT --CS
#define LCD_RST     	GPIO_Pin_12	//PB12连接至TFT --RST
#define LCD_SCL        	GPIO_Pin_13	//PB13连接至TFT -- CLK
#define LCD_SDA        	GPIO_Pin_15	//PB15连接至TFT - SDI
*******************************************************************************/

#define SCLK        3	//PB13--->>TFT --SCL/SCK
#define MISO        4	
#define MOSI        5	//PB15 MOSI--->>TFT --SDA/DIN

#define SPI_MOSI  PBout(MOSI)
#define SPI_SCLK  PBout(SCLK)
#define SPI_MISO  PBin(MISO)

//液晶控制口置1操作语句宏定义

#define	SPI_MOSI_SET  	SPI_MOSI=1 //LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	SPI_SCLK=1 //LCD_CTRL->BSRR=SPI_SCLK    


//液晶控制口置0操作语句宏定义

#define	SPI_MOSI_CLR  	SPI_MOSI=0 //LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	SPI_SCLK=0 //LCD_CTRL->BRR=SPI_SCLK    

void  SPIv_WriteData(u8 Data);


#endif
