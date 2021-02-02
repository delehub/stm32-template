//==================================================================================================
//  文件名称: STM32F103xxxx_USART.H
//  文件功能: USART-USART通信总线
//  文件说明: 无
//==================================================================================================

#ifndef __UART_H__
#define __UART_H__

//--------------------------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "stm32f10x_usart.h"

//--------------------------------------------------------------------------------------------------
// 宏自定义声明     |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  兼容STM32系列单片机 GPIO端口宏定义
#define USARTx1                             USART1
#define USARTx2                             USART2
#define USARTx3                             USART3
#define UARTx4                              UART4
#define UARTx5                              UART5

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define STM32F103xxxx_USARTx1                       1       // USARTx1 开关开启  取值范围 - 0为禁用 1为启用  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_BAUD                  115200  // USARTx1 波特率  取值范围 - 600/1200/2400/4800/9600/19200/38400/115200
#define STM32F103xxxx_USARTx1_PORT_A09A10           1       // USARTx1 引脚设置 PA9 - TxD PA10 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_PORT_B06B07           0       // USARTx1 引脚设置 PB6 - TxD PB7 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_ITEN_RXNE             0       // USARTx1 接受中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_ITEN_IDLE             0       // USARTx1 空闲中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_ITEN_TC               0       // USARTx1 发送完成中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_DMA_TX                0       // USARTx1 DMA发送 开关  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_DMA_RX                0       // USARTx1 DMA接受 开关  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx1_DMA_TX_CUNT           1024    // USARTx1 DMA发送 字节数量
#define STM32F103xxxx_USARTx1_DMA_RX_CUNT           1024    // USARTx1 DMA接受 字节数量
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define STM32F103xxxx_USARTx2                       0       // USARTx2 开关开启  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx2_BAUD                  9600    // USARTx2 波特率  取值范围 - 600/1200/2400/4800/9600/19200/38400/115200
#define STM32F103xxxx_USARTx2_PORT_A02A03           1       // USARTx2 引脚设置 PA2 - TxD PA3 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx2_PORT_D05D06           0       // USARTx2 引脚设置 PD5 - TxD PD6 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx2_ITEN_RXNE             0       // USARTx2 接受中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx2_ITEN_IDLE             0       // USARTx2 空闲中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx2_ITEN_TC               0       // USARTx2 发送完成中断操作使能  取值范围 - 0为禁用 1为启用
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define STM32F103xxxx_USARTx3                       0       // USARTx3 开关开启  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_BAUD                  115200  // USARTx3 波特率  取值范围 - 600/1200/2400/4800/9600/19200/38400/115200
#define STM32F103xxxx_USARTx3_PORT_B10B11           1       // USARTx3 引脚设置 PB10 - TxD PB11 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_PORT_C10C11           0       // USARTx3 引脚设置 PC10 - TxD PC11 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_PORT_D08D09           0       // USARTx3 引脚设置 PD8 - TxD PD9 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_ITEN_RXNE             0       // USARTx3 接受中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_ITEN_IDLE             0       // USARTx3 空闲中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_ITEN_TC               0       // USARTx3 发送完成中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_USARTx3_DMA_TX                0       // USARTx3 DMA发送 开关开启  取值范围 - 0为禁用 1为使能
#define STM32F103xxxx_USARTx3_DMA_RX                0       // USARTx3 DMA接受 开关开启  取值范围 - 0为禁用 1为使能
#define STM32F103xxxx_USARTx3_DMA_TX_COUNT          1024    // USARTx3 DMA发送 字节数量
#define STM32F103xxxx_USARTx3_DMA_RX_COUNT          1024    // USARTx3 DMA接受 字节数量
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define STM32F103xxxx_UARTx4                        0       // UARTx4 开关开启  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx4_BAUD                   115200  // UARTx4 波特率  取值范围 - 600/1200/2400/4800/9600/19200/38400/115200
#define STM32F103xxxx_UARTx4_PORT_C10C11            1       // UARTx4 引脚设置 PC10 - TxD PC11 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx4_ITEN_RXNE              1       // UARTx4 接受中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx4_ITEN_IDLE              0       // UARTx4 空闲中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx4_ITEN_TC                0       // UARTx4 发送完成中断操作使能  取值范围 - 0为禁用 1为启用
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
#define STM32F103xxxx_UARTx5                        0       // UARTx5 开关开启  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx5_BAUD                   115200  // UARTx5 波特率  取值范围 - 600/1200/2400/4800/9600/19200/38400/115200
#define STM32F103xxxx_UARTx5_PORT_C12D02            1       // UARTx5 引脚设置 PC10 - TxD PC11 - RxD  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx5_ITEN_RXNE              1       // UARTx5 接受中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx5_ITEN_IDLE              0       // UARTx5 空闲中断操作使能  取值范围 - 0为禁用 1为启用
#define STM32F103xxxx_UARTx5_ITEN_TC                0       // UARTx5 发送完成中断操作使能  取值范围 - 0为禁用 1为启用

//--------------------------------------------------------------------------------------------------
//  数据变量定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  函数调用声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  USART 预配置
void USART_Configure(void);

//  USART 发送字符、字符串
void USART_SendChar(USART_TypeDef* USARTx, unsigned char Char);
void USART_SendString(USART_TypeDef* USARTx, unsigned char *String);

//  USART 接受字符
unsigned char USART_ReceiveChar(USART_TypeDef* USARTx);

//  USART 发送数组 
void USART_SendArray(USART_TypeDef* USARTx, unsigned char *Array, unsigned char Count);

//  USART 发送回车换行
void USART_SendLine(USART_TypeDef* USARTx);

//  USART 发送数字 
void USART_SendNumber_SignedInteger(USART_TypeDef* USARTx, signed short int Number, unsigned char Count);
void USART_SendNumber_UnsignedInteger(USART_TypeDef* USARTx, unsigned short int Number, unsigned char Count);
void USART_SendNumber_Float(USART_TypeDef* USARTx, float Number, unsigned char Count1, unsigned char Count2);
void USART_SendNumber_Binary(USART_TypeDef* USARTx, int Number, unsigned char Count);






#endif // #ifndef __STM32F103xxxx_USART_H__
