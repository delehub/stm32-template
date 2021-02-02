#ifndef __USART_H__
#define __USART_H__

#include "sys.h"
#include <stdio.h>
/*******************************************************************************
// STM32C串口1 中断测试
*******************************************************************************/ 

//--------------------------------------------------------------------------------------------------
//  宏自定义声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#define USART_REC_LEN  			200  	//定义最大接收字节数 200

#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define EN_USART2_RX 			1		//使能（1）/禁止（0）串口1接收  	
#define EN_USART3_RX 			1		//使能（1）/禁止（0）串口1接收 

#define EN_USART4_RX 			1		//使能（1）/禁止（0）串口1接收  	
#define EN_USART5_RX 			1		//使能（1）/禁止（0）串口1接收 


#define  DEBUG_USARTx                   USART1
//--------------------------------------------------------------------------------------------------
//  定义引用变量    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//如果想串口中断接收，请不要注释以下宏定义
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         	    	//接收状态标记	




//==================================================================================================
//  实现功能: 串口配置函数
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

void USART1_Configuration(u32 bound);
void USART2_Configuration(u32 bound);
void USART3_Configuration(u32 bound);
void UART4_Configuration(u32 bound);
void UART5_Configuration(u32 bound);

int fputc(int ch, FILE *f);//重定向c库函数printf到串口，重定向后可使用printf函数
int fgetc(FILE *f);//重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//==================================================================================================
//  实现功能: 串口发送函数
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void UART_SendChar(USART_TypeDef* USARTx,unsigned char Char);
void UART_SendString(USART_TypeDef* USARTx,unsigned char *String);
unsigned char UART_ReceiveChar(USART_TypeDef* USARTx);
//  USART 发送数组 
void UART_SendArray(USART_TypeDef* USARTx, unsigned char *Array, unsigned char Count);

//  USART 发送回车换行
void UART_SendLine(USART_TypeDef* USARTx);

//  USART 发送数字 
void UART_SendNumber_SignedInteger(USART_TypeDef* USARTx, signed short int Number, unsigned char Count);
void UART_SendNumber_UnsignedInteger(USART_TypeDef* USARTx, unsigned short int Number, unsigned char Count);
void UART_SendNumber_Float(USART_TypeDef* USARTx, float Number, unsigned char Count1, unsigned char Count2);
void UART_SendNumber_Binary(USART_TypeDef* USARTx, int Number, unsigned char Count);


void SendData(USART_TypeDef* USARTx,u8 data);
void SendString(USART_TypeDef* USARTx,u8 *DAT,u8 len);


#endif



