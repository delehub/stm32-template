#include "sys.h"

#ifndef _SOSFSPI_H_
#define _SOFTSPI_H_


//本测试程序使用的是模拟SPI接口驱动
//可自由更改接口IO配置，使用任意最少4 IO即可完成本款液晶驱动显示
/******************************************************************************
接口定义在lcd.h内定义，请根据接线修改并修改相应IO初始化LCD_GPIO_Init()
#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口
#define LCD_LED        	GPIO_Pin_9  //PB9 连接至TFT -LED
#define LCD_RS         	GPIO_Pin_0	//PB10连接至TFT --RS
#define LCD_CS        	GPIO_Pin_1 //PB11 连接至TFT --CS
#define LCD_RST     	  GPIO_Pin_12	//PB12连接至TFT --RST
#define LCD_SCL        	GPIO_Pin_13	//PB13连接至TFT -- CLK
#define LCD_SDA        	GPIO_Pin_15	//PB15连接至TFT - SDI
*******************************************************************************/

#define LCD_CTRL   	  	GPIOB		//定义TFT数据端口
#define SPI_SCLK        GPIO_Pin_13	//PB13--->>TFT --SCL/SCK
#define SPI_MISO        GPIO_Pin_14	
#define SPI_MOSI        GPIO_Pin_15	//PB15 MOSI--->>TFT --SDA/DIN

//液晶控制口置1操作语句宏定义

#define	SPI_MOSI_SET  	LCD_CTRL->BSRR=SPI_MOSI    
#define	SPI_SCLK_SET  	LCD_CTRL->BSRR=SPI_SCLK    


//液晶控制口置0操作语句宏定义

#define	SPI_MOSI_CLR  	LCD_CTRL->BRR=SPI_MOSI    
#define	SPI_SCLK_CLR  	LCD_CTRL->BRR=SPI_SCLK    

void  SPIv_WriteData(u8 Data);

#endif
