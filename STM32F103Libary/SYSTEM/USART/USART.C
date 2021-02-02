#include "USART.H"
#include "gizwits_product.h"
//==================================================================================================
//  实现功能: USART1_Configuration串口配置配置
//  函数说明: USART1初始化函数
//  函数备注: bound:波特率
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
#if EN_USART1_RX   //如果使能了接收  
// 使用串口中断时 解除注释 #if EN_USART1_RX 
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  

void USART1_Configuration(u32 bound)
{
	//GPIO端口设置
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟

	//USART1_TX   GPIOA.9
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9

	//USART1_RX	  GPIOA.10初始化
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

	//Usart1 NVIC 配置
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器

	//USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}
//==================================================================================================
//  实现功能: USART1_IRQHandler串口中断服务函数
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 r;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断
	{
		r =USART_ReceiveData(USART1);//(USART1->DR);	//读取接收到的数据
		USART_SendData(USART1,r);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC) != SET);
	} 
	USART_ClearFlag(USART1,USART_FLAG_TC);
} 	



#endif

//==================================================================================================
//  实现功能: USART2_Configuration串口配置配置
//  函数说明: USART2初始化函数
//  函数备注: bound:波特率
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

//#if EN_USART2_RX   //如果使能了接收

void USART2_Configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;        

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //USART2 TX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure); //端口A；

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //USART2 RX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
    GPIO_Init(GPIOA, &GPIO_InitStructure); //端口A；

    USART_InitStructure.USART_BaudRate = bound; //波特率；
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
    USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //无硬件流控；
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //收发模式；
    USART_Init(USART2, &USART_InitStructure);//配置串口参数；

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; //中断号；
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级；
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //响应优先级；
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART2, ENABLE); //使能串口；
}


//==================================================================================================
//  实现功能: USART2_IRQHandler串口中断服务函数
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void USART2_IRQHandler(void) //中断处理函数；
{ 
  u8 r;
  if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)  //接收中断
  {
    r =USART_ReceiveData(USART2);//(USART1->DR);	//读取接收到的数据
    USART_SendData(USART2,r);
    while(USART_GetFlagStatus(USART2,USART_FLAG_TC) != SET);
  } 
  USART_ClearFlag(USART2,USART_FLAG_TC);
} 

//#endif

//==================================================================================================
//  实现功能: USART3_Configuration串口配置配置
//  函数说明: USART3初始化函数
//  函数备注: bound:波特率
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

//#if EN_USART3_RX   //如果使能了接收

void USART3_Configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;        

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //USART3 TX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure); //端口B；

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //USART3 RX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
    GPIO_Init(GPIOB, &GPIO_InitStructure); //端口B；

    USART_InitStructure.USART_BaudRate = bound; //波特率；
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
    USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //无硬件流控；
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //收发模式；
    USART_Init(USART3, &USART_InitStructure);//配置串口参数；

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

    NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn; //中断号；
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级；
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //响应优先级；
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
    USART_Cmd(USART3, ENABLE); //使能串口
}


//==================================================================================================
//  实现功能: USART3_IRQHandler串口中断服务函数
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
//void USART3_IRQHandler(void) //中断处理函数；
//{
//  u8 r;
//  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)  //接收中断
//  {
//    r =USART_ReceiveData(USART3);//(USART1->DR);	//读取接收到的数据
//    USART_SendData(USART3,r);
//    while(USART_GetFlagStatus(USART3,USART_FLAG_TC) != SET);
//  } 
//  USART_ClearFlag(USART3,USART_FLAG_TC);
//} 

//串口3中断服务函数
void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART3);		 
		gizPutData(&res, 1);//数据写入到缓冲区
	}  				 											 
}   


//#endif

//==================================================================================================
//  实现功能: UART4_Configuration串口配置配置
//  函数说明: UART4初始化函数
//  函数备注: bound:波特率
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

//#if EN_USART4_RX

void UART4_Configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;        

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4 TX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4 RX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
    GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

    USART_InitStructure.USART_BaudRate = bound; //波特率；
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
    USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //无硬件流控；
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //收发模式；
    USART_Init(UART4, &USART_InitStructure);//配置串口参数；

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

    NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; //中断号；
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级；
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级；
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART4, ENABLE); //使能串口；
}


//==================================================================================================
//  实现功能: UART4_IRQHandler串口中断服务函数
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void UART4_IRQHandler(void) //中断处理函数；
{
  u8 r;
  if(USART_GetITStatus(UART4, USART_IT_RXNE) != RESET)  //接收中断
  {
    r =USART_ReceiveData(UART4);//(USART1->DR);	//读取接收到的数据
    USART_SendData(UART4,r);
    while(USART_GetFlagStatus(UART4,USART_FLAG_TC) != SET);
  } 
  USART_ClearFlag(UART4,USART_FLAG_TC);
} 

//#endif

//==================================================================================================
//  实现功能: UART5_Configuration串口配置配置
//  函数说明: UART5初始化函数
//  函数备注: bound:波特率
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

//#if EN_USART5_RX

void UART5_Configuration(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;        

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //UART5 TX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //UART5 RX；
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；
    GPIO_Init(GPIOD, &GPIO_InitStructure); //端口D；

    USART_InitStructure.USART_BaudRate = bound; //波特率；
    USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；
    USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；
    USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    //无硬件流控；
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    //收发模式；
    USART_Init(UART5, &USART_InitStructure);//配置串口参数；

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

    NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //中断号；
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2; //抢占优先级；
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3; //响应优先级；
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
    USART_Cmd(UART5, ENABLE); //使能串口；
}

//==================================================================================================
//  实现功能: UART5_IRQHandler串口中断服务函数
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void UART5_IRQHandler(void) //中断处理函数；
{
  u8 r;
  if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)  //接收中断
  {
    r =USART_ReceiveData(UART5);//(USART1->DR);	//读取接收到的数据
    USART_SendData(UART5,r);
    while(USART_GetFlagStatus(UART5,USART_FLAG_TC) != SET);
  } 
  USART_ClearFlag(UART5,USART_FLAG_TC);
} 

//#endif


//==================================================================================================
//  函数功能: USART 发送字节
//  函数标记: 内设驱动函数
//  函数说明: 本函数没有考虑发送9位数据可能性
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Byte - 字节  取值范文 - ASCII字符
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendChar(USART_TypeDef* USARTx,unsigned char Char)
{
   while((USARTx -> SR & 0x40) == 0);              // 等待上次发送完成   
    USARTx -> DR = Char;                            // 装载本次发送数据  
}

//==================================================================================================
//  函数功能: USART 接收字符
//  函数标记: 内设驱动函数
//  函数说明: 
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//  输出参量: Char - 待接收字节  取值范围 - ASCII字符
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
unsigned char UART_ReceiveChar(USART_TypeDef* USARTx)
{
    return USARTx->DR;
}

//==================================================================================================
//  函数功能: USART 发送字符串
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            String - 待发送字符串指针  取值范文 - ASCII字符串
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendString(USART_TypeDef* USARTx,unsigned char *String)
{
  while(*String != '\0')                          // \0 表示字符串结束标志，通过检测是否字符串末尾
    {
        UART_SendChar(USARTx, *String);
        String++;
    }
}


//  函数功能: USART 发送数组
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Array - 待发送数组的指针  取值范围 - 指针类型
//            Count - 待发送数组的数量  取值范围 - 0~255
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendArray(USART_TypeDef* USARTx, unsigned char *Array, unsigned char Count)
{
    unsigned char i = 0;                            // 定义局部变量 用于函数循环
    for(i=0; i<Count; i++)
    {
        UART_SendChar(USARTx, Array[i]);    
    }
}

//==================================================================================================
//  函数功能: USART 发送回车换行
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendLine(USART_TypeDef* USARTx)
{
    UART_SendChar(USARTx, 0x0D);                   // 换行
    UART_SendChar(USARTx, 0x0A);                   // 回车
}

//==================================================================================================
//  函数功能: USART 发送有符号整型数字
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Number - 待发送整数  取值范围 - 整型类型 -99999~+99999
//            Count - 显示的位数  取值范围 - 1~5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendNumber_SignedInteger(USART_TypeDef* USARTx, signed short int Number, unsigned char Count)
{
    unsigned char NumberArray[5] = {0};             // 定义局部数组，用于数据存储
    
    // 判断 整型数字正负
    if(Number<0)
    {
        Number = 0 - Number;                        // 负数转整数
        UART_SendChar(USARTx,'-');
    }
    else
    {
        UART_SendChar(USARTx,'+');
    }
        
    // 计算各位数值的字符
    if(Count>4) NumberArray[0]=(Number/10000) % 10 + 0x30; 
    if(Count>3) NumberArray[1]=(Number/1000 ) % 10 + 0x30; 
    if(Count>2) NumberArray[2]=(Number/100  ) % 10 + 0x30; 
    if(Count>1) NumberArray[3]=(Number/10   ) % 10 + 0x30; 
    if(Count>0) NumberArray[4]=(Number/1    ) % 10 + 0x30; 
   
    // 发送串口数据
    UART_SendArray(USARTx,&NumberArray[5-Count],Count);
}

//==================================================================================================
//  函数功能: USART 发送无符号整型数字
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Number - 待发送整数  取值范围 - 整型类型 0~99999
//            Count - 显示的位数  取值范围 - 1~5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendNumber_UnsignedInteger(USART_TypeDef* USARTx, unsigned short int Number, unsigned char Count)
{
    unsigned char NumberArray[5] = {0};             // 定义局部数组，用于数据存储
    
    // 断言检查参数
    
    
    // 执行相关操作
    // 计算各位数值的字符
    if(Count>4) NumberArray[0]=(Number/10000) % 10 + 0x30;
    if(Count>3) NumberArray[1]=(Number/1000 ) % 10 + 0x30;
    if(Count>2) NumberArray[2]=(Number/100  ) % 10 + 0x30;
    if(Count>1) NumberArray[3]=(Number/10   ) % 10 + 0x30;
    if(Count>0) NumberArray[4]=(Number/1    ) % 10 + 0x30;
    
    // 发送串口数据
    UART_SendArray(USARTx,&NumberArray[5-Count],Count);
}

//==================================================================================================
//  函数功能: USART 发送数字 浮点类型
//  函数标记: 内设驱动函数
//  函数说明: 本函数打印浮点数字与实际输入数字存在偏差
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Number - 待发送浮点型数字  取值范围 - -99999.99999~99999.99999
//            Count1 - 整数显示位数  取值范围 - 0~5
//            Count2 - 小数显示位数  取值范围 - 0~5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendNumber_Float(USART_TypeDef* USARTx, float Number, unsigned char Count1, unsigned char Count2)
{
    unsigned char Number_Integer_Array[5];          // 定义局部数组 用于存储整数位各位数据
    unsigned char Number_Decimal_Array[5];          // 定义局部数组 用于存储小数位各位数据

    unsigned long int  Number_Integer = 0;          // 定义局部变量 表示浮点数的整数部分
    unsigned long int  Number_Decimal = 0;          // 定义局部变量 表示浮点数的小数部分

    // 判断 浮点数字正负
    if(Number < 0)
    {
        Number = 0 - Number;
        UART_SendChar(USARTx, '-');
    }
    else
    {
        UART_SendChar(USARTx, '+');
    }
    
    // 限制 发送位数
    // 由于由于float型的有效十进制数值最多为7位，即整数位 + 小数位 数量一定小于等于7
    while((Count1 + Count2 > 7 ))
    {
        if((Count1 > 5) && (Count1 != 0))
        {
            --Count1;
        }
        else
        {
            --Count2;
        }
    }
    
    // 分离 整数位与小数位
    // 取整数部分
    Number_Integer = (unsigned long int)(Number);  
    // 取小数部分 1e5科学计数法表示10000
    Number_Decimal = (unsigned long int)((Number - Number_Integer + 0.000005) * 1e5);
        
    // 计算各位数值的字符
    if(Count1>4) Number_Integer_Array[0]=(Number_Integer/10000) % 10 + 0x30; 
    if(Count1>3) Number_Integer_Array[1]=(Number_Integer/1000 ) % 10 + 0x30; 
    if(Count1>2) Number_Integer_Array[2]=(Number_Integer/100  ) % 10 + 0x30; 
    if(Count1>1) Number_Integer_Array[3]=(Number_Integer/10   ) % 10 + 0x30; 
    if(Count1>0) Number_Integer_Array[4]=(Number_Integer/1    ) % 10 + 0x30; 
    
    if(Count2>0) Number_Decimal_Array[0]=(Number_Decimal/10000) % 10 + 0x30; 
    if(Count2>1) Number_Decimal_Array[1]=(Number_Decimal/1000 ) % 10 + 0x30; 
    if(Count2>2) Number_Decimal_Array[2]=(Number_Decimal/100  ) % 10 + 0x30; 
    if(Count2>3) Number_Decimal_Array[3]=(Number_Decimal/10   ) % 10 + 0x30; 
    if(Count2>4) Number_Decimal_Array[4]=(Number_Decimal/1    ) % 10 + 0x30; 
   
    UART_SendArray(USARTx, &Number_Integer_Array[5-Count1], Count1);       // 显示整数位
    UART_SendChar(USARTx, '.');
    UART_SendArray(USARTx, &Number_Decimal_Array[0],        Count2);       // 显示小数位
}

//==================================================================================================
//  函数功能: USART 发送数字 二进制数字
//  函数标记: 内设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: USARTx - 通道号  取值范围 - USARTx1/USARTx2/USARTx3/UARTx4/UARTx5
//            Number - 待发送有符号长整型数字  取值范围 - -99999.99999~99999.99999
//            Count - 整数显示位数  取值范围 - 0~5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void UART_SendNumber_Binary(USART_TypeDef* USARTx,int Number,unsigned char Count)
{
    unsigned char i = 0;
    
    for(i=Count; i>0; i--)
    {
        if(Number & ( 1 << (Count-1) ))
        {
            UART_SendChar(USARTx,'1');
        }
        else
        {
            UART_SendChar(USARTx,'0');
        }
        Number <<= 1;
    }
}
//==================================================================================================
//  函数功能: 重定向c库函数printf到串口，重定向后可使用printf函数
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(DEBUG_USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
//==================================================================================================
//  函数功能: 重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(DEBUG_USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(DEBUG_USARTx);
}


void SendData(USART_TypeDef* USARTx,u8 data)
{
	while((USARTx->SR&0X40)==0); 
	USARTx->DR = data;
}

void SendString(USART_TypeDef* USARTx,u8 *DAT,u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
	 	SendData(USARTx,*DAT++);
	}	
}

