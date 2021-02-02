//--------------------------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "wdg.h"
#include "led.h"
#include "USART.H"


//==================================================================================================
//  实现功能: 独立看门狗初始化 IWDG_Init 
//  函数说明: 
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

void IWDG_Init(unsigned char prer,u16 rlr) 
{	
 	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //使能对寄存器IWDG_PR和IWDG_RLR的写操作
	
	IWDG_SetPrescaler(prer);  //设置IWDG预分频值:设置IWDG预分频值为64
	
	IWDG_SetReload(rlr);  //设置IWDG重装载值
	
	IWDG_ReloadCounter();  //按照IWDG重装载寄存器的值重装载IWDG计数器
	
	IWDG_Enable();  //使能IWDG
}

//==================================================================================================
//  实现功能: 喂独立看门狗 IWDG_Feed 
//  函数说明:  重载计数值 喂狗 （向 向 IWDG_KR  写入 0XAAAA
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void IWDG_Feed(void)
{   
 	IWDG_ReloadCounter();	//重载计数值									   
}

//==================================================================================================
//  实现功能: 窗口看门狗 	初始化 WWDG_Init 
//  保存WWDG计数器的设置值,默认为最大. 
//  tr   :T[6:0],计数器值 
//  wr   :W[6:0],窗口值 
//  fprer:分频系数（WDGTB）,仅最低2位有效 
//  Fwwdg=PCLK1/(4096*2^fprer). 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 

unsigned char WWDG_CNT=0x7f; 

void WWDG_Init(unsigned char tr,unsigned char wr,u32 fprer)
{ 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);  //   WWDG时钟使能

	WWDG_CNT=tr&WWDG_CNT;   //初始化WWDG_CNT.  
  
	WWDG_SetPrescaler(fprer);////设置IWDG预分频值

	WWDG_SetWindowValue(wr);//设置窗口值

	WWDG_Enable(WWDG_CNT);	 //使能看门狗 ,	设置 counter .                  

	WWDG_ClearFlag();//清除提前唤醒中断标志位 

	WWDG_NVIC_Init();//初始化窗口看门狗 NVIC

	WWDG_EnableIT(); //开启窗口看门狗中断
} 

//==================================================================================================
//  实现功能: 重设置WWDG计数器的值 IWDG_Feed 
//  函数说明:  重载计数值 喂狗 向 IWDG_KR  写入 0XAAAA
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void WWDG_Set_Counter(unsigned char cnt)
{
    WWDG_Enable(cnt);//使能看门狗 ,	设置 counter .	 
}

//==================================================================================================
//  实现功能: 窗口看门狗中断服务配置 WWDG_NVIC_Init 
//  函数说明:  
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void WWDG_NVIC_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = WWDG_IRQn;    //WWDG中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;   //抢占2，子优先级3，组2	
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	 //抢占2，子优先级3，组2	
  NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE; 
	NVIC_Init(&NVIC_InitStructure);//NVIC初始化
}

//==================================================================================================
//  实现功能: 窗口看门狗中断服务函数 WWDG_IRQHandler 
//  函数说明:  
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void WWDG_IRQHandler(void)
{

	WWDG_SetCounter(WWDG_CNT);	  //当禁掉此句后,窗口看门狗将产生复位

	WWDG_ClearFlag();	  //清除提前唤醒中断标志位

  /*中断执行相关操作  判断程序是否出现问题*/ 
	LED1=!LED1;		 //LED状态翻转
  UART_SendString(USART1,"WWDG test \r\n");
}

