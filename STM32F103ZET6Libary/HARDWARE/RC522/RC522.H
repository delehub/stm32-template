#ifndef __RC522_H__
#define __RC522_H__

#include "sys.h"
//--------------------------------------------------------------------------------------------------
//  端口引脚定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------			 
#define RC522_RST_CLK		     RCC_APB2Periph_GPIOA	// 设置RST引脚时钟使能
#define RC522_RST_OUT		     GPIOA						 // 设置RST引脚输出		  
#define RC522_RST_PIN		     GPIO_Pin_1				  // 设置RST引脚号 

#define RC522_SPI_CSN_CLK		 RCC_APB2Periph_GPIOA	// 设置CSN引脚时钟使能
#define RC522_SPI_CSN_OUT		 GPIOA						 // 设置CSN引脚输出		  
#define RC522_SPI_CSN_PIN		 GPIO_Pin_0				  // 设置CSN引脚号 

#define RC522_SPI_SCK_CLK		 RCC_APB2Periph_GPIOA	// 设置SCK引脚时钟使能
#define RC522_SPI_SCK_OUT		 GPIOA						 // 设置SCK引脚输出		  
#define RC522_SPI_SCK_PIN		 GPIO_Pin_2				  // 设置SCK引脚号 

#define RC522_SPI_SDI_CLK		 RCC_APB2Periph_GPIOA	// 设置SDI引脚时钟使能
#define RC522_SPI_SDI_OUT		 GPIOA						 // 设置SDI引脚输出 (主入从出=MISO)		 
#define RC522_SPI_SDI_PIN		 GPIO_Pin_5				  // 设置SDI引脚号 

#define RC522_SPI_SDO_CLK		 RCC_APB2Periph_GPIOA	// 设置SDO引脚时钟使能
#define RC522_SPI_SDO_OUT		 GPIOA                  // 设置SDO引脚输出 (主出从入=MOSI)		 
#define RC522_SPI_SDO_PIN		 GPIO_Pin_4				  // 设置SDO引脚号 


//--------------------------------------------------------------------------------------------------
//  数据变量定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

 

//--------------------------------------------------------------------------------------------------
//  函数调用声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  RC522 初始化 
void RC522_Init(void);

unsigned char RC522_CradGetsNumb(unsigned char *Buff);

unsigned char RC522_CradRegt(void);

unsigned char RC522_CradReadData(unsigned char _Numb,unsigned long *_Data);
unsigned char RC522_CradWrteData(unsigned char _Numb,unsigned long *_Data);

#endif



