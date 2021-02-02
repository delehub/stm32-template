//--------------------------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "oled.h"
#include "stdlib.h"
#include "oledfont.h"  	 
#include "delay.h"
#include "math.h"
//==================================================================================================
//  实现功能: OLED iiC 0.96 接线
//   GND   GND
//   VCC   3.3/5V
//   SDA   PB9
//   SCL   PB8
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

//OLED的显存
//存放格式如下.
//[0]0 1 2 3 ... 127	
//[1]0 1 2 3 ... 127	
//[2]0 1 2 3 ... 127	
//[3]0 1 2 3 ... 127	
//[4]0 1 2 3 ... 127	
//[5]0 1 2 3 ... 127	
//[6]0 1 2 3 ... 127	
//[7]0 1 2 3 ... 127 			

unsigned char OLED_GRAM[128][8];
unsigned char OLED_GRAM_TEMP[128][8];

/**********************************************
//IIC Start
**********************************************/
void IIC_Start()
{

	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
  OLED_SCLK_Set() ;
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

void IIC_Wait_Ack()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/

void Write_IIC_Byte(unsigned char IIC_Byte)
{
	unsigned char i;
	unsigned char m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
			m=da;
		//	OLED_SCLK_Clr();
		m=m&0x80;
		if(m==0x80)
		{OLED_SDIN_Set();}
		else OLED_SDIN_Clr();
			da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
		}


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
	 IIC_Wait_Ack();	
   Write_IIC_Byte(0x00);			//write command
	 IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Command); 
	 IIC_Wait_Ack();	
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);			//D/C#=0; R/W#=0
	IIC_Wait_Ack();	
   Write_IIC_Byte(0x40);			//write data
	IIC_Wait_Ack();	
   Write_IIC_Byte(IIC_Data);
	IIC_Wait_Ack();	
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
   Write_IIC_Data(dat);
  }
	else
 {
   Write_IIC_Command(dat);
	}


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
      OLED_WR_Byte(0xb0+m,OLED_CMD);		//page0-page1
      OLED_WR_Byte(0x00,OLED_CMD);		//low column start address
      OLED_WR_Byte(0x10,OLED_CMD);		//high column start address
      for(n=0;n<128;n++)
      {
        OLED_WR_Byte(fill_Data,OLED_DATA);
      }
	}
}

/***********************Delay****************************************/
void Delay_50ms(unsigned int Delay_50ms)
{
	unsigned int count;
	for(;Delay_50ms>0;Delay_50ms--)
		for(count=6245;count>0;count--);
}

void Delay_1ms(unsigned int Delay_1ms)
{
	unsigned char count;
	while(Delay_1ms--)
	{	
		for(count=0;count<123;count++);
	}
}

				   
//更新显存到LCD		 
void OLED_Refresh_Gram(void)
{
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置―列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置―列高地址   
		for(n=0;n<128;n++)
      OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA); 
	}   
}

//==================================================================================================
//  函数功能: OLED 外设驱动函数部分
//  函数标记: 外设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: 无
//  输出参量: 无
//-------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
//开启OLED显示    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//关闭OLED显示     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear(void)  
{  
	uint8_t count,num;		    
	for(count=0;count<8;count++)  
	{  
		OLED_WR_Byte (0xb0+count,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
    
		for(num=0;num<128;num++)
      OLED_WR_Byte(0x00,OLED_DATA); 
	} //更新显示
}


void OLED_On(void)  
{  
	uint8_t count,num;		    
	for(count=0;count<8;count++)  
	{  
		OLED_WR_Byte (0xb0+count,OLED_CMD);    //设置页地址（0~7）
		OLED_WR_Byte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WR_Byte (0x10,OLED_CMD);      //设置显示位置—列高地址
    
		for(num=0;num<128;num++)
      OLED_WR_Byte(0x01,OLED_DATA); 
	} //更新显示
}



 /**
  * @brief  OLED_Fill，填充整个屏幕
  * @param  fill_Data:要填充的数据
	* @retval 无
  */
void OLED_Fill(unsigned char fill_Data)//全屏填充
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,OLED_CMD);		//page0-page1
		OLED_WR_Byte(0x00,OLED_CMD);		//low column start address
		OLED_WR_Byte(0x10,OLED_CMD);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,OLED_DATA);
			}
	}
}

void OLED_Init(void)
{ 	
 
 	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_5;	  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz
 	GPIO_Init(GPIOB, &GPIO_InitStructure);	  
 	GPIO_SetBits(GPIOB,GPIO_Pin_8|GPIO_Pin_5);
  
  delay_ms(200);

  OLED_WR_Byte(0xAE,OLED_CMD);//--display off
	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
	OLED_WR_Byte(0x81,OLED_CMD); // contract control
	OLED_WR_Byte(0xFF,OLED_CMD);//--128   
	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
	OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WR_Byte(0xC8,OLED_CMD);//Com scan direction
	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
	OLED_WR_Byte(0x00,OLED_CMD);//
	
	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
	OLED_WR_Byte(0x80,OLED_CMD);//
	
	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
	OLED_WR_Byte(0x05,OLED_CMD);//
	
	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WR_Byte(0xF1,OLED_CMD);//
	
	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WR_Byte(0x12,OLED_CMD);//
	
	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
	OLED_WR_Byte(0x30,OLED_CMD);//
	
	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WR_Byte(0x14,OLED_CMD);//
	
	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}  


//显示汉字
//==================================================================================================
//  实现功能: OLED 显示汉字
//  函数标记: 外设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            Chinese - 待显示汉字  取值范围 - 单个汉字组成的字符串
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowCHinese(unsigned char X,unsigned char Y,unsigned char Chinese)
{      			    
	unsigned char count,adder=0;
	OLED_Set_Pos(X,Y);	
  for(count=0;count<16;count++)
  {
    OLED_WR_Byte(CHinese[2*Chinese][count],OLED_DATA);
    adder+=1;
  }	
  OLED_Set_Pos(X,Y+1);	
  for(count=0;count<16;count++)
  {	
    OLED_WR_Byte(CHinese[2*Chinese+1][count],OLED_DATA);
    adder+=1;
  }					
}

//==================================================================================================
//  实现功能: OLED_Set_Pos 定位光标
//  函数标记: 外设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_Set_Pos(unsigned char X, unsigned char Y) 
{ 	
  OLED_WR_Byte(0xb0+Y,OLED_CMD);
	OLED_WR_Byte(((X&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((X&0x0f),OLED_CMD); 
}   

//==================================================================================================
//  实现功能: OLED 清除屏幕区域内容
//  函数标记: 外设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            X_Size - X方向尺寸  取值范围 - 1~127
//            Y_Size - Y方向尺寸  取值范围 - 1~  7
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_AreaClear(unsigned char X, unsigned char Y, unsigned char X_Size, unsigned char Y_Size)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    unsigned char j;                                // 定义局部变量 用于函数循环计数

    
    
    for(i=0; i<(Y_Size/8); i++)                     // 遍历每一行
    {
        OLED_Set_Pos(X, Y+i);                       // 设置显示坐标
        for(j=0; j<X_Size; j++)                     // 遍历每一列
        {
            OLED_WR_Byte(0x00,OLED_DATA);
        }
    }
}

//==================================================================================================
//  实现功能: OLED 指定位置 显示字符 06x08像素
//  函数标记: 应用函数 已完成 
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            Char - 待写字符   取值范围 - ASCII字符
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowChar_06x08(unsigned char X, unsigned char Y, unsigned char Char)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    unsigned char j;                                // 定义局部变量 用于函数循环计数
    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数
    

    
    FontCount=sizeof(OLED_ASCII_06x08_FontCode)/sizeof(OLED_ASCII_06x08_FontCode[0]);

    for(i=0; i<FontCount; i++)                      // 遍历每一字库
    {
        if(Char == OLED_ASCII_06x08_FontCode[i].Char)
        {
            OLED_Set_Pos(X,Y);                      // 设置显示坐标
            for(j=0; j<6; j++)                      // 遍历每一列
            {
                OLED_WR_Byte(OLED_ASCII_06x08_FontCode[i].Code[j],OLED_DATA);
            }
            break;
        }
    }
}

//==================================================================================================
//  实现功能: OLED 指定位置 显示字符串 06x08像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//            3. 06x08像素不能显示汉字 只能显示ASCII字符
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            String - 待显示字符串  取值范围 - ASCII字符串
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowString_06x08(unsigned char X, unsigned char Y, unsigned char *String)
{
  
   
    while(*String)                                  // 判断字符串是否为空 
    {
        OLED_ShowChar_06x08(X, Y, *String);         // 指定位置显示字符
        String++;                                   // 字符串指针移动下一个字节
        X+=6;                                       // X坐标移动下一个位置
    }
}


//==================================================================================================
//  实现功能: OLED 指定位置 显示字符 08x16像素
//  函数标记: 应用函数 已完成 
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            Char - 待显示字符  取值范围 - ASCII字符
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowChar_08x16(unsigned char X, unsigned char Y, unsigned char Char)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    unsigned char j;                                // 定义局部变量 用于函数循环计数
    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数
    

    
    FontCount=sizeof(OLED_ASCII_08x16_FontCode)/sizeof(OLED_ASCII_08x16_FontCode[0]);

    for(i=0; i<FontCount; i++)                      // 循环查询字符字模位置
    {
        if(Char == OLED_ASCII_08x16_FontCode[i].Char)
        {
            OLED_Set_Pos(X,Y);                      // 设置显示坐标 用于显示字符
            for(j=0; j<8; j++)
            {
                OLED_WR_Byte(OLED_ASCII_08x16_FontCode[i].Code[j],OLED_DATA);
            }
            OLED_Set_Pos(X,Y+1);                    // 设置显示坐标 用于显示字符
            for(j=8; j<16; j++)
            {
                OLED_WR_Byte(OLED_ASCII_08x16_FontCode[i].Code[j],OLED_DATA);
            }
            break;
        }
    }
}


//==================================================================================================
//  实现功能: OLED 指定位置 显示中英文混合字符串 08x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 目前能显示英文和汉字混合字符串
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            String - 待显示字符串  取值范围 - ASCII和汉字混合字符串
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowString_16x16(unsigned char X, unsigned char Y, unsigned char *String)
{
    unsigned char Position = 0;                     // 定义局部变量 用于标记字符串位置

    while(*String)
    {
        // 判断字符串中的某字符的编码值是否小于0x80
        // 如果小于0x80 即为ASCII字符
        // 如果大于0x80 即为汉字字符串
        if(*String < 0x80)
        {
            // 显示ASCII字符
            OLED_ShowChar_08x16(X+Position*8, Y, *String);
            String++;                               // 字符串指针移动下一个字节
            Position++;                             // 字符串位置下一个位置
        }
        else
        {
//            // 显示汉字
//            OLED_ShowChinese_16x16(X+Position*8, Y, (unsigned char*)String);
//            String+=2;                              // 字符串指针移动下一个字节
//            Position+=2;                            // 字符串位置下一个位置
        }
    }
}

void OLED_ShowArray_06x08(unsigned char X, unsigned char Y, unsigned char *Array, unsigned char Count)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    unsigned char j;                                // 定义局部变量 用于函数循环计数
    unsigned char k;                                // 定义局部变量 用于函数循环计数
    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数

    
    FontCount=sizeof(OLED_ASCII_06x08_FontCode)/sizeof(OLED_ASCII_06x08_FontCode[0]);

    for(i=0; i<Count; i++)
    {
        for(j=0; j<FontCount; j++)                  // 循环查询字符字模位置
        {
            if(*Array == OLED_ASCII_06x08_FontCode[j].Char)
            {
                OLED_Set_Pos(X,Y);                  // 设置显示坐标 用于显示字符
                for(k=0; k<6; k++)
                {
                    OLED_WR_Byte(OLED_ASCII_06x08_FontCode[j].Code[k],OLED_DATA);
                }
                break;
            }
        }
        Array++;
        X += 6;                                     // 数组位置下一个位置
    }
}
//==================================================================================================
//  实现功能: OLED 指定位置 显示有符号整形数字
//  函数标记: 外设驱动函数
//  函数说明: 1.最大显示5位数字 位置选取不恰当 可能造成数字显示不完全
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            IntegerNumber - 待显示整型数字 取值范围 - -32767~+32768
//            Count - 待显示整型数字长度     取值范围 - 0~5；
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowNumber_SignedInteger_06x08(unsigned char X, unsigned char Y, signed short IntegerNumber, unsigned char Count)
{
    unsigned char IntegerNumber_Array[5]={0};       // 定义局部数组 用于数组数据存储


    // 判断 整型数字正负
    if(IntegerNumber < 0)
    {
        IntegerNumber=0 - IntegerNumber;
        OLED_ShowChar_06x08(X, Y, '-');
    }
    else
    {
        OLED_ShowChar_06x08(X, Y, '+');
    }

    // 计算各位数值的字符
    if(Count>4) IntegerNumber_Array[0] = (IntegerNumber/10000) % 10 + 0x30;
    if(Count>3) IntegerNumber_Array[1] = (IntegerNumber/1000 ) % 10 + 0x30;
    if(Count>2) IntegerNumber_Array[2] = (IntegerNumber/100  ) % 10 + 0x30;
    if(Count>1) IntegerNumber_Array[3] = (IntegerNumber/10   ) % 10 + 0x30;
    if(Count>0) IntegerNumber_Array[4] = (IntegerNumber/1    ) % 10 + 0x30;
    
    // 执行显示操作
    OLED_ShowArray_06x08(X+6, Y, &IntegerNumber_Array[5-Count], Count);
}



//==================================================================================================
//  实现功能: OLED 指定位置 显示无符号整形数字
//  函数标记: 外设驱动函数
//  函数说明: 1.最大显示5位数字 位置选取不恰当 可能造成数字显示不完全
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            IntegerNumber - 待显示整型数字 取值范围 - -32767~+32768
//            Count - 待显示整型数字长度     取值范围 - 0~5；
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowNumber_UnsignedInteger_06x08(unsigned char X, unsigned char Y, unsigned short IntegerNumber, unsigned char Count)
{
    unsigned char IntegerNumber_Array[5]={0};       // 定义局部数组 用于数组数据存储
    

    
    // 计算各位数值的字符
    if(Count>4) IntegerNumber_Array[0] = (IntegerNumber/10000) % 10 + 0x30;
    if(Count>3) IntegerNumber_Array[1] = (IntegerNumber/1000 ) % 10 + 0x30;
    if(Count>2) IntegerNumber_Array[2] = (IntegerNumber/100  ) % 10 + 0x30;
    if(Count>1) IntegerNumber_Array[3] = (IntegerNumber/10   ) % 10 + 0x30;
    if(Count>0) IntegerNumber_Array[4] = (IntegerNumber/1    ) % 10 + 0x30;
    
    // 执行显示操作
    OLED_ShowArray_06x08(X, Y, &IntegerNumber_Array[5-Count], Count);
}

//==================================================================================================
//  实现功能: OLED 指定位置 显示06x08大小的浮点数字
//  函数标记: 外设驱动函数
//  函数说明: float型数据有效数字显示7位 double型数据有效数字16位
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            FloatNumber - 待显示浮点型数字  取值范围 - -99999.99999~99999.99999
//            Count1 - 整数显示位数  取值范围 - 0~5
//            Count2 - 小数显示位数  取值范围 - 0~5
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowNumber_Float_06x08(unsigned char X, unsigned char Y, float FloatNumber, unsigned char Count1, unsigned char Count2)
{
    unsigned char Number_Integer_Array[5];          // 定义局部数组 用于存储整数位各位数据
    unsigned char Number_Decimal_Array[5];          // 定义局部数组 用于存储小数位各位数据

    unsigned long Number_Integer = 0;               // 定义局部变量 表示浮点数的 整数部分
    unsigned long Number_Decimal = 0;               // 定义局部变量 表示浮点数的 小数部分


    
    if(FloatNumber < 0)
    {
        FloatNumber= 0 - FloatNumber;
        OLED_ShowChar_06x08(X,Y,'-');
    }
    else
    {
        OLED_ShowChar_06x08(X,Y,'+');
    }

    //----------------------------------------------------------------------------------------------
    // 限制 显示字符数
    //----------------------------------------------------------------------------------------------
    // 由于由于float型的有效十进制数值最多为7位 即整数位 + 小数位 数量一定小于等于7
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

    Number_Integer = (unsigned long)(FloatNumber);                                      // 取整数部分
    Number_Decimal = (unsigned long)((FloatNumber - Number_Integer + 0.000005) * 1e5);  // 取小数部分 1e5科学计数法

    Number_Integer_Array[0] = Number_Integer/10000 % 10 + 0x30;     // 计算整数部分
    Number_Integer_Array[1] = Number_Integer/ 1000 % 10 + 0x30;
    Number_Integer_Array[2] = Number_Integer/  100 % 10 + 0x30;
    Number_Integer_Array[3] = Number_Integer/   10 % 10 + 0x30;
    Number_Integer_Array[4] = Number_Integer/    1 % 10 + 0x30;

    Number_Decimal_Array[0] = Number_Decimal/10000 % 10 + 0x30;     // 计算小数部分
    Number_Decimal_Array[1] = Number_Decimal/ 1000 % 10 + 0x30;
    Number_Decimal_Array[2] = Number_Decimal/  100 % 10 + 0x30;
    Number_Decimal_Array[3] = Number_Decimal/   10 % 10 + 0x30;
    Number_Decimal_Array[4] = Number_Decimal/    1 % 10 + 0x30;

    OLED_ShowArray_06x08(X+6,            Y, &Number_Integer_Array[5-Count1], Count1);   // 显示整数位
    OLED_ShowChar_06x08( X+(1+Count1)*6, Y, '.');                                       // 显示小数点
    OLED_ShowArray_06x08(X+(2+Count1)*6, Y, &Number_Decimal_Array[0],        Count2);   // 显示小数位
}

//==================================================================================================
//  实现功能: OLED 指定位置 显示06x08大小的二进制数字
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 显示8位二进制数字 主要作为寄存器数据显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            BinaryNumber - 待显示二进制数字  取值范围 - 0~4294967295
//            Count - 二进制显示位数  取值范围 - 1~16
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowNumber_Binary_06x08(unsigned char X, unsigned char Y, unsigned long BinaryNumber, unsigned char Count)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    

    
    for(i=Count; i>0; i--)
    {
        if(BinaryNumber & ( 1 << (Count-1) ))
        {
            OLED_ShowChar_06x08(X, Y, '1');         // 显示二进制字符'1'
        }
        else
        {
            OLED_ShowChar_06x08(X, Y, '0');         // 显示二进制字符'1'
        }
        BinaryNumber <<= 1;                         // 移位运算
        X += 6;                                     // 数组位置下一个位置
    }
}

//==================================================================================================
//  实现功能: OLED 指定位置 显示06x08大小的十六进制数字
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 显示8位二进制数字 主要作为寄存器数据显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            BinaryNumber - 待显示二进制数字  取值范围 - 0~4294967295
//            Count - 二进制显示位数  取值范围 - 1~8
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_ShowNumber_Hex_06x08(unsigned char X, unsigned char Y, unsigned long HexNumber, unsigned char Count)
{
    unsigned char i;                                // 定义局部变量 用于函数循环计数
    unsigned long Number;                           // 定义局部变量 用于装载数据
    

    
    for(i=Count; i>0; i--)
    {
        Number = HexNumber>>(4*(i-1)) & 0x0000000F;
        if(Number<10)
        {
            OLED_ShowChar_06x08(X, Y, '0'+Number); 
        }
        else
        {
            OLED_ShowChar_06x08(X, Y, 'A'+(Number-10)); 
        }
        X += 6;                                     // 数组位置下一个位置
    }
}

//==================================================================================================
//  实现功能: OLED 指定位置 绘制直线数据
//  函数标记: 外设驱动函数
//  函数说明: 该点为8个像素的竖线 并非实际像素点
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            PointData - 直线数据  取值范围 - 0~255
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_DrawLine(unsigned char X, unsigned char Y, unsigned char PointData)
{
    
    
    OLED_WR_Byte(0xB0+Y,OLED_CMD);
    OLED_WR_Byte(((X & 0xF0)>>4) | 0x10,OLED_CMD);
    OLED_WR_Byte( (X & 0x0F)     | 0x01,OLED_CMD);
    OLED_WR_Byte(PointData,OLED_DATA);
}

//==================================================================================================
//  实现功能: OLED 指定位置 绘制图像 Draw_BMP
//  函数标记: 外设驱动函数
//  函数说明: 
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 0~127
//            Y - Y方向坐标  取值范围 - 0~  7
//            X_Size - X方向尺寸大小 取值范围 - 0~127
//            Y_Size - Y方向尺寸大小 取值范围 - 0~7
//            Image - 图像数据
//  输出参量: 无
/*功能描述：显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7*****************/
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Draw_BMP(unsigned char X0,unsigned char Y0,unsigned char X1,unsigned char Y1,unsigned char BMP[])
{
	unsigned int j=0;
	unsigned char x,y;

  if(Y1%8==0) y=Y1/8;      
  else y=Y1/8+1;
	for(y=Y0;y<Y1;y++)
	{
		OLED_Set_Pos(X0,y);
    for(x=X0;x<X1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);
	    }
	}
}

//==================================================================================================
////  实现功能: OLED 指定位置 画点
////  函数标记: 外设驱动函数
////  函数说明: 
////--------------------------------------------------------------------------------------------------
////  输入参量: //画点 
//////              //x:0~127
//////              //y:0~63
//////              //t:1 填充 0,清空	
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_DrawDot(unsigned char X,unsigned char Y,unsigned char T)
{
	  unsigned char pos,bx,temp=0;
		if(X>127||Y>63) return;
		pos=(Y)/8;
		bx=Y%8;
		temp=1<<(bx);
		if(T) OLED_GRAM[X][pos]|=temp;
		else OLED_GRAM[X][pos]&=~temp;
		OLED_Refresh_Gram();	
}
//==================================================================================================
//  实现功能: OLED LCD_DrawLine画直线函数
//  函数标记: 外设驱动函数
//  函数说明: 
//--------------------------------------------------------------------------------------------------
//  输入参量: unsigned int X1,  直线：俩点坐标(x1,y1  ,(x2,y2)
//            unsigned int Y1, 
//            unsigned int X2,
//            unsigned int Y2，
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLCD_DrawLine(unsigned int X1, unsigned int Y1, unsigned int X2,unsigned int Y2)
{
	unsigned int t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol;
  
	delta_x=X2-X1; //计算坐标增量 
	delta_y=Y2-Y1; 
	uRow=X1; 
	uCol=Y1; 
  
	if(delta_x>0)
  {
    incx=1; //设置单步方向 
  }
    
	else if(delta_x==0)
  {
    incx=0;//垂直线 
  }
	else 
  {
     incx=-1;
     delta_x=-delta_x;
  } 
  
	if(delta_y>0)
    incy=1; 
	else if(delta_y==0)
    incy=0;//水平线 
	else
  {
    incy=-1;
    delta_y=-delta_y;
  } 
	if( delta_x>delta_y)
    distance=delta_x; //选取基本增量坐标轴 
	else 
    distance=delta_y; 
  
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		OLED_DrawDot(uRow,uCol,1);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  

//================================================================================================== 
///**
// * @brief  在 oled 显示器上使用 Bresenham 算法画圆
// * @param  usX_Center ：在特定扫描方向下圆心的X坐标
// * @param  usY_Center ：在特定扫描方向下圆心的Y坐标
// * @param  usRadius：圆的半径（单位：像素）
// * @param  ucFilled ：选择是否填充该圆
//  *   该参数为以下值之一：
//  *     @arg 0 :空心圆
//  *     @arg 1 :实心圆
// * @retval 无
// */
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_DrawCircle( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled )
{
	int16_t sCurrentX, sCurrentY;
	int16_t sError;
	
	
	sCurrentX = 0; sCurrentY = usRadius;	  
	
	sError = 3 - ( usRadius << 1 );     //判断下个点位置的标志
	
	
	while ( sCurrentX <= sCurrentY )
	{
		int16_t sCountY;
		
		
		if ( ucFilled ) 			
            for ( sCountY = sCurrentX; sCountY <= sCurrentY; sCountY ++ ) 
            {                      
                OLED_DrawDot ( usX_Center + sCurrentX, usY_Center + sCountY,OLED_DATA );           //1，研究对象 
                OLED_DrawDot ( usX_Center - sCurrentX, usY_Center + sCountY,OLED_DATA);           //2       
                OLED_DrawDot ( usX_Center - sCountY,   usY_Center + sCurrentX,OLED_DATA);           //3
                OLED_DrawDot ( usX_Center - sCountY,   usY_Center - sCurrentX,OLED_DATA );           //4
                OLED_DrawDot ( usX_Center - sCurrentX, usY_Center - sCountY,OLED_DATA );           //5    
                OLED_DrawDot ( usX_Center + sCurrentX, usY_Center - sCountY,OLED_DATA );           //6
                OLED_DrawDot ( usX_Center + sCountY,   usY_Center - sCurrentX,OLED_DATA );           //7 	
                OLED_DrawDot ( usX_Center + sCountY,   usY_Center + sCurrentX,OLED_DATA );           //0				
            }	
		else
		{          
                OLED_DrawDot ( usX_Center + sCurrentX, usY_Center + sCurrentY,OLED_DATA );             //1，研究对象
                OLED_DrawDot ( usX_Center - sCurrentX, usY_Center + sCurrentY,OLED_DATA );             //2      
                OLED_DrawDot ( usX_Center - sCurrentY, usY_Center + sCurrentX,OLED_DATA );             //3
                OLED_DrawDot ( usX_Center - sCurrentY, usY_Center - sCurrentX,OLED_DATA );             //4
                OLED_DrawDot ( usX_Center - sCurrentX, usY_Center - sCurrentY,OLED_DATA );             //5       
                OLED_DrawDot ( usX_Center + sCurrentX, usY_Center - sCurrentY,OLED_DATA);             //6
                OLED_DrawDot ( usX_Center + sCurrentY, usY_Center - sCurrentX,OLED_DATA);             //7 
                OLED_DrawDot ( usX_Center + sCurrentY, usY_Center + sCurrentX,OLED_DATA );             //0
    }					
		sCurrentX ++;		
		if ( sError < 0 ) 
			sError += 4 * sCurrentX + 6;	  
		else
		{
			sError += 10 + 4 * ( sCurrentX - sCurrentY );   
			sCurrentY --;
		} 		
	}	
}

//==================================================================================================
//  实现功能: OLED LCD_DrawRectangle
//  函数标记: 外设驱动函数
//  函数说明: 
//--------------------------------------------------------------------------------------------------
//  输入参量: unsigned int X1,  长度 宽度：俩点坐标(x1,y1  ,(x2,y2)
//            unsigned int Y1, 
//            unsigned int X2,
//            unsigned int Y2，
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

void OLCD_DrawRectangle(unsigned short X1, unsigned short Y1, unsigned short X2, unsigned short Y2)
{
        OLCD_DrawLine(X1,Y1,X2,Y1);
        OLCD_DrawLine(X1,Y1,X1,Y2);
        OLCD_DrawLine(X1,Y2,X2,Y2);
        OLCD_DrawLine(X2,Y1,X2,Y2);
}
//==================================================================================================
//  实现功能: OLED OLED_Fill_Draw_circle //画圆填充
//  函数标记: 外设驱动函数
//  函数说明: 
//--------------------------------------------------------------------------------------------------
//  输入参量: //写画实心圆心(x0,y0),半径r，dot=1填充，dot=0不填充
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void OLED_Fill_Draw_circle(unsigned char X0,unsigned char Y0,unsigned char r,unsigned char dot)
{	
		unsigned char x = 0,y = 0,R = 0;
		for(x = X0-r;x <= X0+r;x++)
    {
				for(y = Y0-r; y <= Y0+r ;y++ )
        {
					R = sqrt(pow(r,2)-pow(x-X0,2))+Y0; //圆方程  x,y反置		
					if( (y >= Y0 && y <= R) || (y < Y0 && y >= 2*Y0-R )|| dot == 0 )
          {  //点限制在 圆方程内	
            OLED_DrawDot(y,x,dot);
          }	
				}
		}
}

//==================================================================================================
//  实现功能: OLED_RollDisplay
//  函数标记: 外设驱动函数
//  函数说明: //水平滚动
//  函数完成情况：有问题
//--------------------------------------------------------------------------------------------------
//  输入参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

void OLED_RollDisplay(void)
{
        OLED_WR_Byte(0x2E,OLED_CMD);        //关闭滚动
        OLED_WR_Byte(0x29,OLED_CMD);        //水平向左或者右滚动 2A/29
        OLED_WR_Byte(0x00,OLED_CMD);        //虚拟字节
        OLED_WR_Byte(0x00,OLED_CMD);        //起始页 0
        OLED_WR_Byte(0x07,OLED_CMD);        //滚动时间间隔
        OLED_WR_Byte(0x07,OLED_CMD);        //终止页 7
        OLED_WR_Byte(0x00,OLED_CMD);        //虚拟字节
        OLED_WR_Byte(0xFF,OLED_CMD);        //虚拟字节
        OLED_WR_Byte(0x2F,OLED_CMD);        //开启滚动
}





       
