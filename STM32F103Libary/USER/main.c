//--------------------------------------------------------------------------------------------------
//  包含的系统外设头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "sys.h"
#include "delay.h"
#include "USART.H"

#include "timer.h"
#include "adc.h"
#include <math.h>
#include "wdg.h" 
//--------------------------------------------------------------------------------------------------
//  包含的外部驱动头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "led.h"
#include "LCD.H"
#include "QDTFT_demo.h"
#include "Picture.h"
#include "key.h"
#include "oled.h"
#include "beep.h"
#include "dht11.h"
#include "bh1750.h"
#include "syn6288.h"


//--------------------------------------------------------------------------------------------------
//  网络协议驱动头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "gizwits_product.h" //机智云网络协议驱动
//--------------------------------------------------------------------------------------------------
//  宏自定义声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  定义引用变量    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//unsigned char num;
/* u8 unsigned char u16 unsigned short  u32 unsigned int  u64 unsigned long*/

unsigned short MQ135_ADC,MQ2_ADC,MQ4_ADC,MQ7_ADC;//ADC采集值
float temp1,temp2,temp3,temp4,MQ135_quality,MQ2_quality,MQ4_quality,MQ7_quality,Light; //实际转换值
extern u8 DHT11_Temp,DHT11_Hum;		//温湿度    
    
unsigned int time1 =0;
unsigned int timeCount1=0;
unsigned int timeflag1 =0; 

unsigned int time2 =0;
unsigned int timeCount2=0;
unsigned int timeflag2 =0; 

unsigned int time3 =0;
unsigned int timeCount3=0;
unsigned int timeflag3 =0; 

unsigned int time4 =0;
unsigned int timeCount4=0;
unsigned int timeflag4 =0;

unsigned int Basictime =0;
unsigned int BasictimeCount=0;
unsigned int Basictimeflag =0; 

unsigned char IC_Card[4]={0};
//--------------------------------------------------------------------------------------------------
//  硬件端口定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  引用函数声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

void LED_TEST(void);
void Hareware_Iint(void);
void TFT_ShowTEST(void);
void Usart_Test(void);
void oled_test(void);
void Timer_Configure(void);
void GeneralTimer_Test(void);
void Basic_Timer_Test(void);
void Basic_GeneralTimer_Test(void);
void USart_Configure(void);
void DHT11_DisPlay(void);//温湿度显示函数
void Gas_sensorGet_Data(void);//获取传感器数据
void IWdg_Test(void);
void LED_PWM_Test(void);
void BH1750_Test(void);
void Gizwits_Init(void);
void RFID_Test(void);
void PWM_Test(void);
//==================================================================================================
//  实现功能: 硬件初始化配置
//  函数说明: Hareware_Iint
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Hareware_Iint(void)
{
    delay_init();	 // 延迟函数配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
//  Timer_Configure();//定时器配置
    USART1_Configuration(115200);//串口1配置
    LED_Init();	//板载LED配置
    KEY_Init(); //板载独立按键测试
    OLED_Init(); // IIC 0.96 oled
    Lcd_Init();  //ST7735 LCD配置
    LCD_LED_SET; //设置背光
    Lcd_Clear(WHITE); //清屏 
    BEEP_Init();//蜂鸣器配置
    BH1750_Init();//光照传感器配置 
    Adc_Init();//ADC配置
    
    #if 0
    /*独立看门狗配置*/
    IWDG_Init(4,625);    //与分频数为64,重载值为625,溢出时间为1s	
    /*窗口看门狗配置*/
    WWDG_Init(0X7F,0X5F,WWDG_Prescaler_8);//计数器值为7f,窗口寄存器为5f,分频数为8	   
    #endif 
//    TIM3_PWM_Init(899,0);	 //不分频。PWM频率=72000000/900=80Khz


    Gizwits_Init();//机智云配置

    
     
}
//==================================================================================================
//  实现功能: LED测试函数
//  函数说明: PB5 LED0  PE5 LED1
//  函数备注: 板载LED 正常 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void LED_TEST(void)
{
      LED0=0;
      delay_ms(500);
      LED0=1;
      delay_ms(500);
      LED1=0;
      delay_ms(500);
      LED1=1;
      delay_ms(500);
}
//==================================================================================================
//  实现功能: TFT_ShowTEST测试函数
//  函数说明: 
//  函数备注: ST7735 TFTLCD 测试正常
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void  TFT_ShowTEST(void)
{
      // Redraw_Mainmenu();
      Num_Test();
      // Font_Test();
      Color_Test();
      //TFT_ShowImage(gImage_qq);
    
      Lcd_Clear(WHITE); //清屏 
      TFT_ShowString_16x16(0,16,"stm32 vscode",Red,White);
      delay_ms(1000);
      TFT_ShowNumber_SignedInteger_16x16(16,32,1234,5,Red,White);
      delay_ms(1000);
      TFT_ShowNumber_Float_16x16(0,48,123.56,4,3,Red,White);
      delay_ms(1000);
      TFT_ShowString_16x16(16,60,"By 2021-01-29",Red,White);
      delay_ms(1000);
      TFT_ShowString_16x16(0,90,"keil5 vscode",Red,White);
      delay_ms(1000);
      
}
//==================================================================================================
//  实现功能: 串口配置配置
//  函数说明: TIM2,3,4,5
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void USart_Configure(void)
{
//    UART4_Configuration(9600);//串口4配置
//    USART1_Configuration(115200);//串口1配置
}
//==================================================================================================
//  实现功能: Usart_Test测试函数
//  函数说明: 串口配置测试函数  STM32F103ZET6 5个串口
//  函数备注: USART1  USART2 USART3 UART4 UART5 
//   TX端口   PA9     PA2    PB10   PC10  PC12
//   RX端口   PA10    PA3    PB11   PC11  PD2
//  串口1~5 测试正常 打印效果正常
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void Usart_Test(void)
{
  
  #if 0
  UART_SendString(USART1,"usart1 test \r\n");
  delay_ms(500);
  TFT_ShowString_16x16(0,0,"usart1 test",Red,White);
  #endif
  
  #if 0
  UART_SendString(USART2,"usart2 test \r\n");
  delay_ms(500);
  TFT_ShowString_16x16(0,16,"usart2 test",Red,White);
  #endif
  
  #if 0
  UART_SendString(USART3,"usart3 test \r\n");
  delay_ms(500);
  TFT_ShowString_16x16(0,32,"usart3 test",Red,White);
  #endif
  
  #if 0
  UART_SendString(UART4,"uart4 test \r\n");
  delay_ms(500);
  TFT_ShowString_16x16(0,48,"uart4 test",Red,White);
  #endif
  
  #if 0 
  UART_SendString(UART5,"uart5 test \r\n");
  delay_ms(500);
  TFT_ShowString_16x16(0,54,"uart5 test",Red,White);
  #endif
  
  #if 1 
  UART_SendNumber_SignedInteger(USART1,123,4);
  UART_SendLine(USART1);
  delay_ms(500);
  UART_SendNumber_UnsignedInteger(USART1,123,4);
  UART_SendLine(USART1);
  delay_ms(500);
  UART_SendNumber_Float(USART1,123.56,4,3);
  UART_SendLine(USART1);
  delay_ms(500);
  UART_SendNumber_Binary(USART1,9,4);
  UART_SendLine(USART1);
  delay_ms(500);
  
  #endif
  
  
}

//==================================================================================================
//  实现功能: oled_test测试函数
//  函数说明: 采用软件IIC 进行配置   SDA PB9  SCL in 
//  函数备注:  测试正常
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void oled_test(void)
{
  OLED_ShowChar_08x16(0,0,'@');
  OLED_ShowChar_08x16(16,0,'&');
  OLED_ShowNumber_SignedInteger_06x08(0,2,1234,5);
  OLED_ShowNumber_UnsignedInteger_06x08(48,2,1234,5);
  OLED_ShowNumber_Float_06x08(0,4,123.46,3,3);
  OLED_ShowString_06x08(32,0,"oled");
  OLED_ShowCHinese(0,6,0);
  OLED_ShowCHinese(16,6,1);
  OLED_ShowCHinese(32,6,2);
  OLED_ShowCHinese(48,6,3);
  OLED_ShowCHinese(64,6,4);
//  OLED_Clear();
}
//==================================================================================================
//  实现功能: Key_Test 按键测试函数
//  函数说明: KEY0 PE4 KEY1 PE3 KEY_WK_UP PA0
//  函数备注: KEY0_PRES 1  KEY1_PRES 1  WKUP_PRES 3 
//----------------------------------------- ---------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void Key_Test(void)
{
      unsigned char key_value=0;
      TFT_ShowString_16x16(0,0,"KEY:",Red,White);
      key_value=KEY_Scan(0);
  
      if(key_value==3)
      {
        TFT_ShowNumber_SignedInteger_16x16(60,0,key_value,2,Red,White);
        //USART_SendString(USART1,"key_value:3 \r\n");
      }
      if(key_value==2)
      {
        TFT_ShowNumber_SignedInteger_16x16(60,0,key_value,2,Red,White);
        //USART_SendString(USART1,"key_value:2 \r\n");
      }
      if(key_value==1)
      {
        TFT_ShowNumber_SignedInteger_16x16(60,0,key_value,2,Red,White);
        //USART_SendString(USART1,"key_value:1 \r\n");
      }
}
//==================================================================================================
//  实现功能: 定时器配置 1s测试
//  函数说明: TIM2,3,4,5
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void Timer_Configure(void)
{
    /*定时器配置*/
    BASIC_TIM_Init();
    TIM5_Init(9999,7199);
//    TIM3_Int_Init(9999,7199);
    TIM2_Int_Init(9999,7199);
    TIM4_Int_Init(9999,7199);
    
}
//==================================================================================================
//  实现功能: 通用定时器定时器测试
//  函数说明: TIM2,3,4,5
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================  
void GeneralTimer_Test(void)
{
  if ( timeflag1 == 1 )  // TIM5
    {
      timeflag1 = 0;
      timeCount1++;     
			LED1=!LED1; 
      
      if (timeCount1 == 60)
      {
        timeCount1=0;
      }
      TFT_ShowNumber_SignedInteger_16x16(90,32,timeCount1,2,Blue1,White);
    }  

    
    if ( timeflag2 == 1 )  //TIM3     
    {
      timeflag2 = 0;
      timeCount2++;    

      if (timeCount2 == 60)
      {
        timeCount2=0;
      }
      TFT_ShowNumber_SignedInteger_16x16(90,60,timeCount2,2,Blue1,White);
    } 

     if ( timeflag3 == 1 )   //TIM2  
    {
      timeflag3 = 0;
      timeCount3++;    

      if (timeCount3 == 60)
      {
        timeCount3=0;
      }
      TFT_ShowNumber_SignedInteger_16x16(90,90,timeCount3,2,Green,White);
    }  
    
    if ( timeflag4 == 1 )  //TIM4   
    {
      timeflag4 = 0;
      timeCount4++;    

      if (timeCount4 == 60)
      {
        timeCount4=0;
      }
      TFT_ShowNumber_SignedInteger_16x16(90,120,timeCount4,2,Green,White);
    }   
}
//==================================================================================================
//  实现功能: 基本定时器定时器测试
//  函数说明: TIM6,7
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void Basic_Timer_Test(void)
{
   if ( Basictime == 1000 ) /* 1000 * 1 ms = 1s 时间到 */      
    {
      Basictime = 0;
      BasictimeCount++;    

      if (BasictimeCount == 60)
      {
        BasictimeCount=0;
      }
      TFT_ShowNumber_SignedInteger_16x16(90,140,BasictimeCount,2,Black,White);
    } 
}

//==================================================================================================
//  实现功能: 定时器定时 1s 测试
//  函数说明:  
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void Basic_GeneralTimer_Test(void)
{
  GeneralTimer_Test();//通用定时器定时器测试
  Basic_Timer_Test();//基本定时器定时器测试
}

#if 0

    TFT_ShowString_16x16(0,0,"stm32 timertest",Magenta,White);
    TFT_ShowString_16x16(0,32,"timeCount1 ",Blue1,White);
    TFT_ShowString_16x16(0,60,"timeCount2 ",Red,White);
    TFT_ShowString_16x16(0,90,"timeCount3 ",Red,White);
    TFT_ShowString_16x16(0,120,"timeCount4",Red,White);
    TFT_ShowString_16x16(0,140,"Basictime",Magenta,White);

#endif
//==================================================================================================
//  实现功能: DHT11_DisPlay 显示温湿度传感器数值
//  函数说明:  
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void DHT11_DisPlay(void)
{
       //循环外 硬件初始化之后
       TFT_ShowString_16x16(0,0,"TEMP:",Magenta,White);
       TFT_ShowString_16x16(0,32,"Hum: ",Blue1,White);
       //循环内 循环获取温湿度值更新
       DHT11_Read_Data(&DHT11_Temp,&DHT11_Hum);
       TFT_ShowNumber_Float_16x16(32,0,DHT11_Temp,2,1,Red,White);
       TFT_ShowNumber_Float_16x16(32,32,DHT11_Hum,2,1,Green,White);  
}
//==================================================================================================
//  实现功能: Gas_sensorGet_Data 显示温湿度传感器数值
//  函数说明:  
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void Gas_sensorGet_Data(void)
{      
  #if 0
       unsigned short MQ135_ADC,MQ2_ADC;
       float temp1,temp2,MQ135_quality,MQ2_quality;
  
       DHT11_Read_Data(&DHT11_Temp,&DHT11_Hum); 
       TFT_ShowString_16x16(0,0,"TEMP:",Magenta,White);
       TFT_ShowString_16x16(0,16,"Hum: ",Blue1,White); 
       TFT_ShowString_16x16(0,32,"MQ-2:",Magenta,White);
       TFT_ShowString_16x16(0,48,"MQ-135:",Blue1,White);
      
      
       MQ135_ADC=Get_Adc_Average(ADC_Channel_11,10);  
       temp1=(float)MQ135_ADC*(3.3/4096);
		   MQ135_quality=pow((11.5428 * 35.904 * temp1 )/(25.5 - 5.1 * temp1),1.0/0.6549);
		   MQ135_ADC=temp1;
		   temp1-=MQ135_ADC;
      
      
      
       MQ2_ADC = Get_Adc_Average(ADC_Channel_13,10);
       temp2=(float)MQ2_ADC*(3.3/4096);
       MQ2_quality = pow((11.5428 * 35.904 * temp2 )/(25.5 - 5.1 * temp2),1.0/0.6549);
       MQ2_ADC=temp2;
		   temp2-=MQ2_ADC;
  
  
       TFT_ShowNumber_Float_16x16(40,0,DHT11_Temp,2,1,Red,White);
       TFT_ShowNumber_Float_16x16(40,16,DHT11_Hum,2,1,Green,White); 
       TFT_ShowNumber_Float_16x16(66,32,MQ2_quality,4,1,Magenta,White);  
       TFT_ShowNumber_Float_16x16(66,48,MQ135_quality,4,1,Magenta,White); 
       
    #endif   
      
}
//==================================================================================================
//  实现功能: 独立看门狗 窗口看门狗测试
//  函数说明: 窗口看门狗
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void IWdg_Test(void)
{
   if(KEY_Scan(0) == WKUP_PRES ) 
   {
      IWDG_Feed();//如果WK_UP按下,则喂狗 执行相关操作复位
      UART_SendString(USART1,"IWDG test \r\n");
   }  
}
//==================================================================================================
//  实现功能: 定时器 PWM 功能 测试
//  函数说明: 呼吸灯效果
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void LED_PWM_Test(void)
{
    //相关变量 Hareware_Iint() 之前定义
    unsigned short Led0PwmVal=0;
    unsigned Incordecflag=1;//是否增加 减小 flag=1 增加 flag=0 减小
  
    //相关变量 while(1)  循环内部使用
//     delay_ms(10);
      
      if(Incordecflag)
      {
        Led0PwmVal++;
      }
      else
      {
        Led0PwmVal--;
      }
      
      if(Led0PwmVal > 900)
      {
        Incordecflag=0;
      }
        
      if(Led0PwmVal == 0)
      {
          Incordecflag=1;
      }
      
      TIM_SetCompare2(TIM3,Led0PwmVal); 
}
//==================================================================================================
//  实现功能: 定时器 PWM原理
//  说明:STM32F103Z系列 TIM1,TIM8 可以实现7路PWM波输出，通用定时器可以产生4路输出
//  控制PWM寄存器
//  捕获/比较模式寄存器（TIMx_CCMR1/2）CCMR1-->CH1 CH2 CCMR2-->CH3 CH4 
//	捕获/比较使能寄存器（TIMx_CCER）
//	捕获/比较寄存器（TIMx_CCR1~4) 对应 4 个输通道 CH1--CH4
//  STM32的重映射控制是由复用重映射和调试 IO 配置寄存器（AFIO_MAPR）控制
//
//
//
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void PWM_Test(void)
{
	
}
//==================================================================================================
//  实现功能: 机智云协议配置
//  函数说明: 进行ESP8266配网操作
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void Gizwits_Init(void)
{
	TIM3_Int_Init(9,7199);//1MS系统定时
	USART3_Configuration(9600);//WIFI初始化
	userInit();//设备状态结构体初始化
	gizwitsInit();//缓冲区初始化 
  
  
}
//==================================================================================================
//  实现功能: RFID_Test
//  函数说明: 串口打印卡号
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//================================================================================================== 
void RFID_Test(void)
{
 
}
////==================================================================================================
////  实现功能: 主函数
////  函数说明: 
////  函数备注: 
////--------------------------------------------------------------------------------------------------
////  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
////==================================================================================================  
int main(void)          
{	
   
  
    Hareware_Iint();//硬件初始化配置
    

    while(1) 
    {
				TFT_ShowTEST();
      
    }  

  
}















