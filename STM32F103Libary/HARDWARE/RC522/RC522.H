#ifndef __RC522_H__
#define __RC522_H__

#include "sys.h"
//--------------------------------------------------------------------------------------------------
//  �˿����Ŷ���    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------			 
#define RC522_RST_CLK		     RCC_APB2Periph_GPIOA	// ����RST����ʱ��ʹ��
#define RC522_RST_OUT		     GPIOA						 // ����RST�������		  
#define RC522_RST_PIN		     GPIO_Pin_1				  // ����RST���ź� 

#define RC522_SPI_CSN_CLK		 RCC_APB2Periph_GPIOA	// ����CSN����ʱ��ʹ��
#define RC522_SPI_CSN_OUT		 GPIOA						 // ����CSN�������		  
#define RC522_SPI_CSN_PIN		 GPIO_Pin_0				  // ����CSN���ź� 

#define RC522_SPI_SCK_CLK		 RCC_APB2Periph_GPIOA	// ����SCK����ʱ��ʹ��
#define RC522_SPI_SCK_OUT		 GPIOA						 // ����SCK�������		  
#define RC522_SPI_SCK_PIN		 GPIO_Pin_2				  // ����SCK���ź� 

#define RC522_SPI_SDI_CLK		 RCC_APB2Periph_GPIOA	// ����SDI����ʱ��ʹ��
#define RC522_SPI_SDI_OUT		 GPIOA						 // ����SDI������� (����ӳ�=MISO)		 
#define RC522_SPI_SDI_PIN		 GPIO_Pin_5				  // ����SDI���ź� 

#define RC522_SPI_SDO_CLK		 RCC_APB2Periph_GPIOA	// ����SDO����ʱ��ʹ��
#define RC522_SPI_SDO_OUT		 GPIOA                  // ����SDO������� (��������=MOSI)		 
#define RC522_SPI_SDO_PIN		 GPIO_Pin_4				  // ����SDO���ź� 


//--------------------------------------------------------------------------------------------------
//  ���ݱ�������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

 

//--------------------------------------------------------------------------------------------------
//  ������������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  RC522 ��ʼ�� 
void RC522_Init(void);

unsigned char RC522_CradGetsNumb(unsigned char *Buff);

unsigned char RC522_CradRegt(void);

unsigned char RC522_CradReadData(unsigned char _Numb,unsigned long *_Data);
unsigned char RC522_CradWrteData(unsigned char _Numb,unsigned long *_Data);

#endif


