//----------------  ----------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//*******************************************************************************
//本程序适用与STM32F103ZET6
//              GND   电源地
//              VCC   接5V或3.3v电源
//              SCL   接PA5（SCL）
//              SDA   接PA7（SDA）
//              RST   接PB0
//              DC    接PB1
//              CS    接PA4 
//							BL		接PA1
//*******************************************************************************


#include "sys.h"
#include "LCD.h"
#include "delay.h"
#include "font.h"
//#include "Picture.h"

//--------------------------------------------------------------------------------------------------
//  宏自定义声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  定义引用变量    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//初始化PB5和PE5为输出口
//--------------------------------------------------------------------------------------------------
//  硬件端口定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  引用函数声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------


//==================================================================================================
//  实现功能: LCD_GPIO_Init
//  函数说明: //液晶IO初始化配置
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

void LCD_GPIO_Init(void)
{

	GPIO_InitTypeDef  GPIO_InitStructure;
	      
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
      
	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA ,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_1|GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

//==================================================================================================
//  实现功能: SPI_WriteData
//  函数说明: 向SPI总线传输一个8位数据
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void  SPI_WriteData(unsigned char Data)
{
	unsigned char i=0;
	for(i=8;i>0;i--)
	{
			if(Data&0x80)	
			LCD_SDA_SET; //输出数据
			else LCD_SDA_CLR;
	   
      LCD_SCL_CLR;       
      LCD_SCL_SET;
      Data<<=1; 
	}
}
//==================================================================================================
//  实现功能: Lcd_WriteIndex
//  函数说明: 向液晶屏写一个8位指令
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Lcd_WriteIndex(unsigned char Index)
{
   //SPI 写命令时序开始
   LCD_CS_CLR;
   LCD_RS_CLR;
	 SPI_WriteData(Index);
   LCD_CS_SET;
}
//==================================================================================================
//  实现功能: Lcd_WriteData
//  函数说明: 向液晶屏写一个8位数据
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Lcd_WriteData(unsigned char Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
   SPI_WriteData(Data);
   LCD_CS_SET; 
}
//==================================================================================================
//  实现功能: LCD_WriteData_16Bit
//  函数说明: 向液晶屏写一个16位数据
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
//向液晶屏写一个16位数据
void LCD_WriteData_16Bit(unsigned short Data)
{
   LCD_CS_CLR;
   LCD_RS_SET;
	 SPI_WriteData(Data>>8); 	//写入高8位数据
	 SPI_WriteData(Data); 			//写入低8位数据
   LCD_CS_SET; 
}
//==================================================================================================
//  实现功能: Lcd_WriteReg
//  函数说明: 写寄存器内容函数
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Lcd_WriteReg(unsigned char Index,unsigned char Data)
{
	Lcd_WriteIndex(Index);
  Lcd_WriteData(Data);
}

//==================================================================================================
//  实现功能: Lcd_Reset
//  函数说明: LCD复位
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Lcd_Reset(void)
{
	LCD_RST_CLR;
	delay_ms(100);
	LCD_RST_SET;
	delay_ms(50);
}
//==================================================================================================
//  实现功能: Lcd_Init
//  函数说明: LCD硬件初始化
//  函数备注: //LCD Init For 1.44Inch LCD Panel with ST7735R.
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

void Lcd_Init(void)
{	
	LCD_GPIO_Init();
	Lcd_Reset(); //Reset before LCD Init.

	//LCD Init For 1.44Inch LCD Panel with ST7735R.
	Lcd_WriteIndex(0x11);//Sleep exit 
	delay_ms (120);
		
	//ST7735R Frame Rate
	Lcd_WriteIndex(0xB1); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB2); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 

	Lcd_WriteIndex(0xB3); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	Lcd_WriteData(0x01); 
	Lcd_WriteData(0x2C); 
	Lcd_WriteData(0x2D); 
	
	Lcd_WriteIndex(0xB4); //Column inversion 
	Lcd_WriteData(0x07); 
	
	//ST7735R Power Sequence
	Lcd_WriteIndex(0xC0); 
	Lcd_WriteData(0xA2); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x84); 
	Lcd_WriteIndex(0xC1); 
	Lcd_WriteData(0xC5); 

	Lcd_WriteIndex(0xC2); 
	Lcd_WriteData(0x0A); 
	Lcd_WriteData(0x00); 

	Lcd_WriteIndex(0xC3); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0x2A); 
	Lcd_WriteIndex(0xC4); 
	Lcd_WriteData(0x8A); 
	Lcd_WriteData(0xEE); 
	
	Lcd_WriteIndex(0xC5); //VCOM 
	Lcd_WriteData(0x0E); 
	
	Lcd_WriteIndex(0x36); //MX, MY, RGB mode 
	Lcd_WriteData(0xC0); 
	
	//ST7735R Gamma Sequence
	Lcd_WriteIndex(0xe0); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1a); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x18); 
	Lcd_WriteData(0x2f); 
	Lcd_WriteData(0x28); 
	Lcd_WriteData(0x20); 
	Lcd_WriteData(0x22); 
	Lcd_WriteData(0x1f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x23); 
	Lcd_WriteData(0x37); 
	Lcd_WriteData(0x00); 	
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x02); 
	Lcd_WriteData(0x10); 

	Lcd_WriteIndex(0xe1); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x1b); 
	Lcd_WriteData(0x0f); 
	Lcd_WriteData(0x17); 
	Lcd_WriteData(0x33); 
	Lcd_WriteData(0x2c); 
	Lcd_WriteData(0x29); 
	Lcd_WriteData(0x2e); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x30); 
	Lcd_WriteData(0x39); 
	Lcd_WriteData(0x3f); 
	Lcd_WriteData(0x00); 
	Lcd_WriteData(0x07); 
	Lcd_WriteData(0x03); 
	Lcd_WriteData(0x10);  
	
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x7f);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x00);
	Lcd_WriteData(0x9f);
	
	Lcd_WriteIndex(0xF0); //Enable test command  
	Lcd_WriteData(0x01); 
	Lcd_WriteIndex(0xF6); //Disable ram power save mode 
	Lcd_WriteData(0x00); 
	
	Lcd_WriteIndex(0x3A); //65k mode 
	Lcd_WriteData(0x05); 
	
	
	Lcd_WriteIndex(0x29);//Display on	 
}


/*************************************************
函数名：LCD_Set_Region
功能：设置lcd显示区域，在此区域写点数据自动换行
入口参数：xy起点和终点
返回值：无
*************************************************/
void Lcd_SetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end)
{		
	Lcd_WriteIndex(0x2a);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_start);//Lcd_WriteData(x_start+2);
	Lcd_WriteData(0x00);
	Lcd_WriteData(x_end+2);

	Lcd_WriteIndex(0x2b);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_start+0);
	Lcd_WriteData(0x00);
	Lcd_WriteData(y_end+1);
	
	Lcd_WriteIndex(0x2c);

}

/*************************************************
函数名：LCD_Set_XY
功能：设置lcd显示起始点
入口参数：xy坐标
返回值：无
*************************************************/
void Lcd_SetXY(unsigned short x,unsigned short y)
{
  	Lcd_SetRegion(x,y,x,y);
}

	
/*************************************************
函数名：LCD_DrawPoint
功能：画一个点
入口参数：无
返回值：无
*************************************************/
void Gui_DrawPoint(unsigned short x,unsigned short y,unsigned short Data)
{
	Lcd_SetRegion(x,y,x+1,y+1);
	LCD_WriteData_16Bit(Data);

}    

/*****************************************
 函数功能：读TFT某一点的颜色                          
 出口参数：color  点颜色值                                 
******************************************/
unsigned int Lcd_ReadPoint(unsigned short x,unsigned short y)
{
  unsigned int Data;
  Lcd_SetXY(x,y);
  Lcd_WriteData(Data);
  return Data;
}
/*************************************************
函数名：Lcd_Clear
功能：全屏清屏函数
入口参数：填充颜色COLOR
返回值：无
*************************************************/
void Lcd_Clear(unsigned short Color)               
{	
   unsigned int i,m;
   Lcd_SetRegion(0,0,X_MAX_PIXEL-1,Y_MAX_PIXEL-1);
   Lcd_WriteIndex(0x2C);
   for(i=0;i<X_MAX_PIXEL;i++)
    for(m=0;m<Y_MAX_PIXEL;m++)
    {	
	  	LCD_WriteData_16Bit(Color);
    }   
}

//==================================================================================================
//  实现功能: LCD_BGR2RGB
//  函数说明: 
  //读出的数据为GBR格式，而我们写入的时候为RGB格式。
  //通过该函数转换
  //c:GBR格式的颜色值
  //返回值：RGB格式的颜色值
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
unsigned short LCD_BGR2RGB(unsigned short c)
{
  unsigned short  r,g,b,rgb;   
  b=(c>>0)&0x1f;
  g=(c>>5)&0x3f;
  r=(c>>11)&0x1f;	 
  rgb=(b<<11)+(g<<5)+(r<<0);		 
  return(rgb);

}
//==================================================================================================
//  实现功能: Gui_Circle
//  函数说明: 画圆函数
//  函数备注: Bresenham算法 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Gui_Circle(unsigned short X,unsigned short Y,unsigned short R,unsigned short fc) 
{
    unsigned short  a,b; 
    int c; 
    a=0; 
    b=R; 
    c=3-2*R; 
    while (a<b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc);     //        7 
        Gui_DrawPoint(X-a,Y+b,fc);     //        6 
        Gui_DrawPoint(X+a,Y-b,fc);     //        2 
        Gui_DrawPoint(X-a,Y-b,fc);     //        3 
        Gui_DrawPoint(X+b,Y+a,fc);     //        8 
        Gui_DrawPoint(X-b,Y+a,fc);     //        5 
        Gui_DrawPoint(X+b,Y-a,fc);     //        1 
        Gui_DrawPoint(X-b,Y-a,fc);     //        4 

        if(c<0) c=c+4*a+6; 
        else 
        { 
            c=c+4*(a-b)+10; 
            b-=1; 
        } 
       a+=1; 
    } 
    if (a==b) 
    { 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y+b,fc); 
        Gui_DrawPoint(X+a,Y-b,fc); 
        Gui_DrawPoint(X-a,Y-b,fc); 
        Gui_DrawPoint(X+b,Y+a,fc); 
        Gui_DrawPoint(X-b,Y+a,fc); 
        Gui_DrawPoint(X+b,Y-a,fc); 
        Gui_DrawPoint(X-b,Y-a,fc); 
    } 
	
} 

//==================================================================================================
//  实现功能: Gui_DrawLine
//  函数说明: 画线函数
//  函数备注: 画线函数，使用Bresenham 画线算法
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Gui_DrawLine(unsigned short x0, unsigned short y0,unsigned short x1, unsigned short y1,unsigned short Color)   
{
  int dx,             // difference in x's
      dy,             // difference in y's
      dx2,            // dx,dy * 2
      dy2, 
      x_inc,          // amount in pixel space to move during drawing
      y_inc,          // amount in pixel space to move during drawing
      error,          // the discriminant i.e. error i.e. decision variable
      index;          // used for looping	
	
      Lcd_SetXY(x0,y0);
      dx = x1-x0;//计算x距离
      dy = y1-y0;//计算y距离

      if (dx>=0)
      {
        x_inc = 1;
      }
      else
      {
        x_inc = -1;
        dx    = -dx;  
      } 
      
      if (dy>=0)
      {
        y_inc = 1;
      } 
      else
      {
        y_inc = -1;
        dy    = -dy; 
      } 

      dx2 = dx << 1;
      dy2 = dy << 1;

    if (dx > dy)//x距离大于y距离，那么每个x轴上只有一个点，每个y轴上有若干个点
    {//且线的点数等于x距离，以x轴递增画点
      // initialize error term
      error = dy2 - dx; 

      // draw the line
      for (index=0; index <= dx; index++)//要画的点数不会超过x距离
      {
        //画点
        Gui_DrawPoint(x0,y0,Color);
        
        // test if error has overflowed
        if (error >= 0) //是否需要增加y坐标值
        {
          error-=dx2;

          // move to next line
          y0+=y_inc;//增加y坐标值
        } // end if error overflowed

        // adjust the error term
        error+=dy2;

        // move to the next pixel
        x0+=x_inc;//x坐标值每次画点后都递增1
      } // end for
    } // end if |slope| <= 1
    else//y轴大于x轴，则每个y轴上只有一个点，x轴若干个点
    {//以y轴为递增画点
      // initialize error term
      error = dx2 - dy; 

      // draw the line
      for (index=0; index <= dy; index++)
      {
        // set the pixel
        Gui_DrawPoint(x0,y0,Color);

        // test if error overflowed
        if (error >= 0)
        {
          error-=dy2;

          // move to next line
          x0+=x_inc;
        } // end if error overflowed

        // adjust the error term
        error+=dx2;

        // move to the next pixel
        y0+=y_inc;
      } // end for
    } // end else |slope| > 1
  }

//==================================================================================================
//  实现功能: Gui_box
//  函数说明: 画矩形函数
//  函数备注: 
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================

void Gui_box(unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned short bc)
{
	Gui_DrawLine(x,y,x+w,y,0xEF7D);
	Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
	Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
	Gui_DrawLine(x,y,x,y+h,0xEF7D);
  Gui_DrawLine(x+1,y+1,x+1+w-2,y+1+h-2,bc);
}

void Gui_box2(unsigned short x,unsigned short y,unsigned short w,unsigned short h, unsigned char mode)
{
	if (mode==0)	 
  {
		Gui_DrawLine(x,y,x+w,y,0xEF7D);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0x2965);
		Gui_DrawLine(x,y+h,x+w,y+h,0x2965);
		Gui_DrawLine(x,y,x,y+h,0xEF7D);
	}
	if (mode==1)	
  {
		Gui_DrawLine(x,y,x+w,y,0x2965);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xEF7D);
		Gui_DrawLine(x,y+h,x+w,y+h,0xEF7D);
		Gui_DrawLine(x,y,x,y+h,0x2965);
	}
	if (mode==2)	
  {
		Gui_DrawLine(x,y,x+w,y,0xffff);
		Gui_DrawLine(x+w-1,y+1,x+w-1,y+1+h,0xffff);
		Gui_DrawLine(x,y+h,x+w,y+h,0xffff);
		Gui_DrawLine(x,y,x,y+h,0xffff);
	}
}


/**************************************************************************************
功能描述: 在屏幕显示一凸起的按钮框
输    入: unsigned short x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonDown(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, GRAY2);  //H
	Gui_DrawLine(x1+1,y1+1,x2,y1+1, GRAY1);  //H
	Gui_DrawLine(x1,  y1,  x1,y2, GRAY2);  //V
	Gui_DrawLine(x1+1,y1+1,x1+1,y2, GRAY1);  //V
	Gui_DrawLine(x1,  y2,  x2,y2, WHITE);  //H
	Gui_DrawLine(x2,  y1,  x2,y2, WHITE);  //V
}

/**************************************************************************************
功能描述: 在屏幕显示一凹下的按钮框
输    入: unsigned short x1,y1,x2,y2 按钮框左上角和右下角坐标
输    出: 无
**************************************************************************************/
void DisplayButtonUp(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2)
{
	Gui_DrawLine(x1,  y1,  x2,y1, WHITE); //H
	Gui_DrawLine(x1,  y1,  x1,y2, WHITE); //V
	
	Gui_DrawLine(x1+1,y2-1,x2,y2-1, GRAY1);  //H
	Gui_DrawLine(x1,  y2,  x2,y2, GRAY2);  //H
	Gui_DrawLine(x2-1,y1+1,x2-1,y2, GRAY1);  //V
  Gui_DrawLine(x2  ,y1  ,x2,y2, GRAY2); //V
}

//==================================================================================================
//  实现功能: Gui_DrawFont_GBK16
//  函数说明: 
//  函数备注: fc:font Color  bc :background Color
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Gui_DrawFont_GBK16(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned char *s)
{
	unsigned char i,j;
	unsigned short k,x0;
	x0=x;

	while(*s) 
	{	
		if((*s) < 128) 
		{
			k=*s;
			if (k==13) 
			{
				x=x0;
				y+=16;
			}
			else 
			{
				if (k>32) k-=32; else k=0;
	
			    for(i=0;i<16;i++)
				for(j=0;j<8;j++) 
					{
				    	if(asc16[k*16+i]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
						else 
						{
							if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
						}
					}
				x+=8;
			}
			s++;
		}
			
		else 
		{
			for (k=0;k<hz16_num;k++) 
			{
			  if ((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<16;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2]&(0x80>>j))	Gui_DrawPoint(x+j,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz16[k].Msk[i*2+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
				    }
				}
			  }
			s+=2;x+=16;
		} 
		
	}
}
//==================================================================================================
//  实现功能: Gui_DrawFont_GBK24
//  函数说明: 
//  函数备注: fc:font Color  bc :background Color
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Gui_DrawFont_GBK24(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned char *s)
{
	unsigned char i,j;
	unsigned short k;

	while(*s) 
	{
		if( *s < 0x80 ) 
		{
			k=*s;
			if (k>32) k-=32; else k=0;

		    for(i=0;i<16;i++)
			for(j=0;j<8;j++) 
				{
			    	if(asc16[k*16+i]&(0x80>>j))	
					Gui_DrawPoint(x+j,y+i,fc);
					else 
					{
						if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
					}
				}
			s++;x+=8;
		}
		else 
		{

			for (k=0;k<hz24_num;k++) 
			{
			  if ((hz24[k].Index[0]==*(s))&&(hz24[k].Index[1]==*(s+1)))
			  { 
				    for(i=0;i<24;i++)
				    {
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3]&(0x80>>j))
								Gui_DrawPoint(x+j,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+1]&(0x80>>j))	Gui_DrawPoint(x+j+8,y+i,fc);
								else {
									if (fc!=bc) Gui_DrawPoint(x+j+8,y+i,bc);
								}
							}
						for(j=0;j<8;j++) 
							{
						    	if(hz24[k].Msk[i*3+2]&(0x80>>j))	
								Gui_DrawPoint(x+j+16,y+i,fc);
								else 
								{
									if (fc!=bc) Gui_DrawPoint(x+j+16,y+i,bc);
								}
							}
				    }
			  }
			}
			s+=2;x+=24;
		}
	}
}
//==================================================================================================
//  实现功能: Gui_DrawFont_Num32
//  函数说明: 
//  函数备注: fc:font Color  bc :background Color
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void Gui_DrawFont_Num32(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned short num)
{
	unsigned char i,j,k,c;
    for(i=0;i<32;i++)
	{
		for(j=0;j<4;j++) 
		{
			c=*(sz32+num*32*4+i*4+j);
			for (k=0;k<8;k++)	
			{
		    if(c&(0x80>>k))	
          Gui_DrawPoint(x+j*8+k,y+i,fc);
				else
        {
					if (fc!=bc) 
            Gui_DrawPoint(x+j*8+k,y+i,bc);
				}
			}
		}
	}
}

//==================================================================================================
//  实现功能: TFT 定位光标
//  函数标记: 外设驱动函数
//  函数说明: 无
//--------------------------------------------------------------------------------------------------
//  输入参量: X_Start - X起始坐标  取值范围 - 0~239
//            Y_Start - Y起始坐标  取值范围 - 0~239
//            X_End - X终止坐标  取值范围 - 0~239
//            Y_End - Y终止坐标  取值范围 - 0~239
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_SetArea(unsigned short X_Start,unsigned short Y_Start,unsigned short X_End,unsigned short Y_End)
{


    // 执行相应操作
    #if (TFT_FUNCTION_SCREEEN_VH == 0)      // 竖屏
    {
        Lcd_WriteIndex(0x2A);
        Lcd_WriteData(0x02);
        Lcd_WriteData(X_Start+2);
        Lcd_WriteData(0x02);
        Lcd_WriteData(X_End+2);
        
        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x01);
        Lcd_WriteData(Y_Start+1);
        Lcd_WriteData(0x01);
        Lcd_WriteData(Y_End+1);
    }
    #endif  // #if (TFT_FUNCTION_SCREEEN_VH == 0)

    #if (TFT_FUNCTION_SCREEEN_VH == 1)      // 横屏 待调整
    {
        Lcd_WriteIndex(0x2A);
        Lcd_WriteData(0x02);
        Lcd_WriteData(X_Start+1);
        Lcd_WriteData(0x02);
        Lcd_WriteData(X_End+1);
        
        Lcd_WriteIndex(0x2B);
        Lcd_WriteData(0x01);
        Lcd_WriteData(Y_Start+2);
        Lcd_WriteData(0x01);
        Lcd_WriteData(Y_End+2);
    }
    #endif  // #if (TFT_FUNCTION_SCREEEN_VH == 1)
        
    Lcd_WriteIndex(0x2C);
}


//==================================================================================================
//  实现功能: TFT 指定位置 显示ASCII字符 08x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            ASCII - 待显示ASCII字符  取值范围 - ASCII字符
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowASCII_08x16(unsigned short X, unsigned short Y,unsigned char ASCII, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char i,j,k;                            // 定义局部变量 用于循环计数
    unsigned char Data;                             // 定义局部变量 用于临时存储
    
    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数

    
    FontCount = sizeof(TFT_ASCII_08x16_FontCode)/sizeof(TFT_ASCII_08x16_FontCode[0]);

    for(i=0; i<FontCount; i++)                      // 开始字库内容匹配                             
    {
        if(ASCII == TFT_ASCII_08x16_FontCode[i].Char)
        {
            TFT_SetArea(X, Y, X+8-1, Y+16-1);       // 设置显示位置
            for(j=0; j<16; j++)                     // 循环写入16字节 一个字符信息包含16字节
            {
                Data = TFT_ASCII_08x16_FontCode[i].Code[j];
                for(k=0; k<8; k++)
                {
                    if((Data&0x80) == 0x80)         // 判断最高位是否为1
                    {
                        LCD_WriteData_16Bit(FontColor);             // 最高位为1 写入字符颜色
                    }
                    else
                    {
                        LCD_WriteData_16Bit(BackgroundColor);       // 最高位为0 写入背景颜色
                    }
                    Data <<= 1;
                }
            }
            break;                                  // 结束字库内容匹配                              
        }
    }
}
//==================================================================================================
//  实现功能: TFT 指定位置 显示中文 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//            3. 1个汉字等同2个字节组成
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            Chinese - 待显示汉字  取值范围 - 单个汉字组成的字符串
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowChinese_16x16(unsigned short X, unsigned short Y,unsigned char *Chinese, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char i,j,k;                            // 定义局部变量 用于循环计数
    unsigned char Data;                             // 定义局部变量 用于临时存储

    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数    
  

    FontCount = sizeof(TFT_CHINESE_16x16_FontCode)/sizeof(TFT_CHINESE_16x16_FontCode[0]);

    for(i=0; i<FontCount; i++)                      // 开始字库内容匹配                             
    {
        if((*Chinese     == TFT_CHINESE_16x16_FontCode[i].Char[0])
        && (*(Chinese+1) == TFT_CHINESE_16x16_FontCode[i].Char[1]))
        {
            TFT_SetArea(X, Y, X+16-1, Y+16-1);      // 设置显示位置
            for(j=0; j<32; j++)                     // 循环写入32字节 一个汉字信息包含32字节
            {
                Data = TFT_CHINESE_16x16_FontCode[i].Code[j];
                for(k=0; k<8; k++)
                {
                    if((Data&0x80) == 0x80)         // 判断最高位是否为1
                    {
                        LCD_WriteData_16Bit(FontColor);             // 最高位为1 写入字符颜色
                    }
                    else
                    {
                        LCD_WriteData_16Bit(BackgroundColor);       // 最高位为0 写入背景颜色
                    }
                    Data <<= 1;
                }
            }
            break;                                  // 结束字库内容匹配                              
        }
    }
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示字符串 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            String - 待显示字符串  取值范围 - 字母/数字/符号/汉字混合组成的字符串
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowString_16x16(unsigned short X, unsigned short Y,unsigned char *String, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
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
            TFT_ShowASCII_08x16(X+Position*8, Y, *String, FontColor, BackgroundColor);
            String++;                               // 字符串指针移动下一个字节
            Position++;                             // 字符串位置下一个位置
        }
        else
        {
            // 显示汉字
            TFT_ShowChinese_16x16(X+Position*8, Y, (unsigned char*)String, FontColor, BackgroundColor);
            String+=2;                              // 字符串指针移动下一个字节
            Position+=2;                            // 字符串位置下一个位置
        }
    }
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示中文 24x24像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//            3. 1个汉字等同2个字节组成
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            Chinese - 待显示汉字  取值范围 - 单个汉字组成的字符串
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowChinese_24x24(unsigned short X, unsigned short Y,unsigned char *Chinese, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char i,j,k;                            // 定义局部变量 用于循环计数
    unsigned char Data;                             // 定义局部变量 用于临时存储

    unsigned char FontCount;                        // 定义局部变量 用于记录字符字库个数    
    


    FontCount = sizeof(TFT_CHINESE_24x24_FontCode)/sizeof(TFT_CHINESE_24x24_FontCode[0]);

    for(i=0; i<FontCount; i++)                      // 开始字库内容匹配                             
    {
        if((*Chinese     == TFT_CHINESE_24x24_FontCode[i].Char[0])
        && (*(Chinese+1) == TFT_CHINESE_24x24_FontCode[i].Char[1]))
        {
            TFT_SetArea(X, Y, X+24-1, Y+24-1);      // 设置显示位置
            for(j=0; j<72; j++)                     // 循环写入32字节 一个汉字信息包含32字节
            {
                Data = TFT_CHINESE_24x24_FontCode[i].Code[j];
                for(k=0; k<8; k++)
                {
                    if((Data&0x80) == 0x80)         // 判断最高位是否为1
                    {
                        LCD_WriteData_16Bit(FontColor);             // 最高位为1 写入字符颜色
                    }
                    else
                    {
                        LCD_WriteData_16Bit(BackgroundColor);       // 最高位为0 写入背景颜色
                    }
                    Data <<= 1;
                }
            }
            break;                                  // 结束字库内容匹配                              
        }
    }
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示字符串 24x24像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 如果字库不存在该文字则不显示
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            String - 待显示字符串  取值范围 - 字母/数字/符号/汉字混合组成的字符串
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowString_24x24(unsigned short X, unsigned short Y,unsigned char *String, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
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
            TFT_ShowASCII_08x16(X+Position*8, Y, *String, FontColor, BackgroundColor);
            String++;                               // 字符串指针移动下一个字节
            Position++;                             // 字符串位置下一个位置
        }
        else
        {
            // 显示汉字
            TFT_ShowChinese_24x24(X+Position*8, Y, (unsigned char*)String, FontColor, BackgroundColor);
            String+=2;                              // 字符串指针移动下一个字节
            Position+=3;                            // 字符串位置下一个位置
        }
    }
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示有符号整形数字 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成数字显示不完全
//            2. 注意输入数字的取值范围
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            IntegerNumber - 待显示整型数字  取值范围 - -32767~+32768
//            Count - 待显示整型数字长度      取值范围 - 1~5
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowNumber_SignedInteger_16x16(unsigned short X, unsigned short Y, signed short IntegerNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char Number_Integer_Array[6] = {0};    // 定义局部数据 用于装载显示数据


    
    // 判断数字正负型
    if(IntegerNumber < 0)
    {
        IntegerNumber = 0-IntegerNumber;
        TFT_ShowASCII_08x16(X, Y, '-', FontColor, BackgroundColor);
    }
    else
    {
        TFT_ShowASCII_08x16(X, Y, '+', FontColor, BackgroundColor);
    }

    // 限制显示字符数
    if(Count > 5)
    {
        Count = 5;
    }
    
    // 装载显示字符
    Number_Integer_Array[0] = (IntegerNumber / 10000) % 10 + 0x30;
    Number_Integer_Array[1] = (IntegerNumber / 1000 ) % 10 + 0x30;
    Number_Integer_Array[2] = (IntegerNumber / 100  ) % 10 + 0x30;
    Number_Integer_Array[3] = (IntegerNumber / 10   ) % 10 + 0x30;
    Number_Integer_Array[4] = (IntegerNumber / 1    ) % 10 + 0x30;
    Number_Integer_Array[5] = '\0';
    
    // 执行显示操作
    TFT_ShowString_16x16(X+8, Y, &Number_Integer_Array[5-Count], FontColor, BackgroundColor);
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示无符号整形数字 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成数字显示不完全
//            2. 注意输入数字的取值范围
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            IntegerNumber - 待显示整型数字  取值范围 - -32767~+32768
//            Count - 待显示整型数字长度      取值范围 - 0~5
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowNumber_UnsignedInteger_16x16(unsigned short X, unsigned short Y, unsigned short IntegerNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char Number_Integer_Array[6] = {0};    // 定义局部数据 用于装载显示数据


    
    // 限制 显示字符数
    if(Count > 5)
    {
        Count = 5;
    }

    // 装载显示字符
    Number_Integer_Array[0] = (IntegerNumber / 10000) % 10 + 0x30;
    Number_Integer_Array[1] = (IntegerNumber / 1000 ) % 10 + 0x30;
    Number_Integer_Array[2] = (IntegerNumber / 100  ) % 10 + 0x30;
    Number_Integer_Array[3] = (IntegerNumber / 10   ) % 10 + 0x30;
    Number_Integer_Array[4] = (IntegerNumber / 1    ) % 10 + 0x30;
    Number_Integer_Array[5] = '\0';

    // 执行显示操作
    TFT_ShowString_16x16(X, Y, &Number_Integer_Array[5-Count], FontColor, BackgroundColor);
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示浮点数字 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成数字显示不完全
//            2. float型数据的有效数字7位 double型数据的有效数字16位
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            FloatNumber - 待显示浮点型数字  取值范围 - -99999.99999~99999.99999
//            Count1 - 整数显示位数  取值范围 - 0~5
//            Count2 - 小数显示位数  取值范围 - 0~5
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowNumber_Float_16x16(unsigned short X, unsigned short Y, float FloatNumber, unsigned char Count1, unsigned char Count2, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char Number_Integer_Array[6];          // 定义局部数组 用于存储整数位各位数据
    unsigned char Number_Decimal_Array[6];          // 定义局部数组 用于存储小数位各位数据

    unsigned long int Number_Integer = 0;           // 定义局部变量 表示浮点数的 整数部分
    unsigned long int Number_Decimal = 0;           // 定义局部变量 表示浮点数的 小数部分


    
    // 判断数字正负型
    if(FloatNumber < 0)
    {
        FloatNumber = 0-FloatNumber;
        TFT_ShowASCII_08x16(X, Y, '-', FontColor, BackgroundColor);
    }
    else
    {
        TFT_ShowASCII_08x16(X, Y, '+', FontColor, BackgroundColor);
    }

    // 限制 显示字符数
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

    // 计算浮点数字的整数部分与小数部分
    Number_Integer = (unsigned long int)(FloatNumber);                                          // 取整数部分
    Number_Decimal = (unsigned long int)((FloatNumber - Number_Integer + 0.000005) * 1e5);      // 取小数部分，1e5科学计数法

    // 装载显示字符
    Number_Integer_Array[0] = Number_Integer/10000 % 10 + 0x30;     // 计算整数部分
    Number_Integer_Array[1] = Number_Integer/ 1000 % 10 + 0x30;
    Number_Integer_Array[2] = Number_Integer/  100 % 10 + 0x30;
    Number_Integer_Array[3] = Number_Integer/   10 % 10 + 0x30;
    Number_Integer_Array[4] = Number_Integer/    1 % 10 + 0x30;
    Number_Integer_Array[5] = '\0';

    Number_Decimal_Array[0] = Number_Decimal/10000 % 10 + 0x30;     // 计算小数部分
    Number_Decimal_Array[1] = Number_Decimal/ 1000 % 10 + 0x30;
    Number_Decimal_Array[2] = Number_Decimal/  100 % 10 + 0x30;
    Number_Decimal_Array[3] = Number_Decimal/   10 % 10 + 0x30;
    Number_Decimal_Array[4] = Number_Decimal/    1 % 10 + 0x30;
    Number_Decimal_Array[Count2] = '\0';
    
    // 执行显示操作
    TFT_ShowString_16x16(X+8,            Y, &Number_Integer_Array[5-Count1], FontColor, BackgroundColor);  
    TFT_ShowASCII_08x16( X+(1+Count1)*8, Y, '.',                             FontColor, BackgroundColor);                                           
    TFT_ShowString_16x16(X+(2+Count1)*8, Y, &Number_Decimal_Array[0],        FontColor, BackgroundColor);
}

//==================================================================================================
//  实现功能: TFT 指定位置 显示二进制数字 16x16像素
//  函数标记: 外设驱动函数
//  函数说明: 1. 位置选取不恰当 可能造成字符串显示不完全
//            2. 注意输入数字的取值范围
//--------------------------------------------------------------------------------------------------
//  输入参量: X - X方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_X
//            Y - Y方向坐标  取值范围 - 详情见宏定义TFT_SHOWSIZE_Y
//            BinaryNumber - 待显示二进制数字  取值范围 - 0~65535
//            Count - 二进制显示位数  取值范围 - 1~16
//            FontColor - 字体颜色  取值范围 - 详情见枚举类型enumTFT_Color
//            BackgroundColor - 背景颜色 取值范围 - 详情见枚举类型enumTFT_Color
//  输出参量: 无
//--------------------------------------------------------------------------------------------------
//  |   -   |   -   |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//==================================================================================================
void TFT_ShowNumber_Binary_16x16(unsigned short X, unsigned short Y, unsigned short BinaryNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor)
{
    unsigned char i;                                // 定义局部变量，用于函数循环计数

    
    for(i=Count; i>0; i--)
    {
        if(BinaryNumber & ( 1 << (Count-1) ))
        {
            TFT_ShowASCII_08x16(X, Y, '1', FontColor, BackgroundColor);     // 显示二进制字符'1'
        }
        else
        {
            TFT_ShowASCII_08x16(X, Y, '0', FontColor, BackgroundColor);     // 显示二进制字符'1'
        }
        BinaryNumber <<= 1;                         // 移位运算
        X += 6;                                     // 数组位置下一个位置
    }
}


//取模方式 水平扫描 从左到右 低位在前
void TFT_ShowImage(const unsigned char *p) 
{
  	int i,j,k; 
	unsigned char picH,picL;
	Lcd_Clear(WHITE); //清屏  
	
	for(k=0;k<4;k++)
	{
	   	for(j=0;j<3;j++)
		{	
			Lcd_SetRegion(40*j+2,40*k,40*j+39,40*k+39);		//坐标设置
		    for(i=0;i<40*40;i++)
			 {	
			 	picL=*(p+i*2);	//数据低位在前
				picH=*(p+i*2+1);				
				LCD_WriteData_16Bit(picH<<8|picL);  						
			 }	
		 }
	}		
}



