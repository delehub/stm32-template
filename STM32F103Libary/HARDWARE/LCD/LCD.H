#ifndef __LCD_H
#define __LCD_H	 

		 				    



#define X_MAX_PIXEL	        128
#define Y_MAX_PIXEL	        160

//  TFT 功能选项
#define TFT_FUNCTION_SCREEEN_VH     0            // TFT功能选项 屏幕横竖 取值范围 - 0为默认竖屏 1为横屏


#define RED  	  0xf800
#define GREEN	  0x07e0
#define BLUE 	  0x001f
#define WHITE	  0xffff
#define BLACK	  0x0000
#define YELLOW  0xFFE0
#define GRAY0   0xEF7D   	    //灰色0 3165 00110 001011 00101
#define GRAY1   0x8410      	//灰色1      00000 000000 00000
#define GRAY2   0x4208      	//灰色2  1111111111011111

//  TFT 显示颜色 枚举
typedef enum enumTFT_Color
{
    White   = 0xFFFF,                               // 白色
    Black   = 0x0000,                               // 黑色
    Blue1   = 0x001F,                               // 浅蓝色
    Blue2   = 0x051F,                               // 深蓝色
    Red     = 0xF800,                               // 红色
    Magenta = 0xF81F,                               // 品红色
    Green   = 0x07E0,                               // 绿色
    Cyan    = 0x7FFF,                               // 青色
    Yellow  = 0xFFE0,                               // 黄色
}enumTFT_Color;


#define LCD_CTRLA   	  	GPIOA		//定义TFT数据端口
#define LCD_CTRLB   	  	GPIOB		//定义TFT数据端口

#define LCD_SCL        	GPIO_Pin_5	//PB13--->>TFT --SCL/SCK
#define LCD_SDA        	GPIO_Pin_7	//PB15 MOSI--->>TFT --SDA/DIN
#define LCD_CS        	GPIO_Pin_4  //MCU_PB11--->>TFT --CS/CE

#define LCD_LED        	GPIO_Pin_1  //MCU_PB9--->>TFT --BL
#define LCD_RS         	GPIO_Pin_1	//PB11--->>TFT --RS/DC
#define LCD_RST     	  GPIO_Pin_0	//PB10--->>TFT --RST



//液晶控制口置1操作语句宏定义
#define	LCD_SCL_SET  	LCD_CTRLA->BSRR=LCD_SCL    
#define	LCD_SDA_SET  	LCD_CTRLA->BSRR=LCD_SDA   
#define	LCD_CS_SET  	LCD_CTRLA->BSRR=LCD_CS  

    
#define	LCD_LED_SET  	LCD_CTRLA->BSRR=LCD_LED   
#define	LCD_RS_SET  	LCD_CTRLB->BSRR=LCD_RS 
#define	LCD_RST_SET  	LCD_CTRLB->BSRR=LCD_RST 
//液晶控制口置0操作语句宏定义
#define	LCD_SCL_CLR  	LCD_CTRLA->BRR=LCD_SCL  
#define	LCD_SDA_CLR  	LCD_CTRLA->BRR=LCD_SDA 
#define	LCD_CS_CLR  	LCD_CTRLA->BRR=LCD_CS 
    
#define	LCD_LED_CLR  	LCD_CTRLB->BRR=LCD_LED 
#define	LCD_RST_CLR  	LCD_CTRLB->BRR=LCD_RST
#define	LCD_RS_CLR  	LCD_CTRLB->BRR=LCD_RS 

#define LCD_DATAOUT(x) LCD_DATA->ODR=x; //数据输出
#define LCD_DATAIN     LCD_DATA->IDR;   //数据输入

#define LCD_WR_DATA(data){\
LCD_RS_SET;\
LCD_CS_CLR;\
LCD_DATAOUT(data);\
LCD_WR_CLR;\
LCD_WR_SET;\
LCD_CS_SET;\
} 



void LCD_GPIO_Init(void);
void Lcd_WriteIndex(unsigned char Index);
void Lcd_WriteData(unsigned char Data);
void Lcd_WriteReg(unsigned char Index,unsigned char Data);
unsigned short Lcd_ReadReg(unsigned char LCD_Reg);
void Lcd_Reset(void);
void Lcd_Init(void);
void Lcd_Clear(unsigned short Color);
void Lcd_SetXY(unsigned short x,unsigned short y);
void Gui_DrawPoint(unsigned short x,unsigned short y,unsigned short Data);
unsigned int Lcd_ReadPoint(unsigned short x,unsigned short y);
void Lcd_SetRegion(unsigned short x_start,unsigned short y_start,unsigned short x_end,unsigned short y_end);
void LCD_WriteData_16Bit(unsigned short Data);

unsigned short LCD_BGR2RGB(unsigned short c);
void Gui_Circle(unsigned short X,unsigned short Y,unsigned short R,unsigned short fc); 
void Gui_DrawLine(unsigned short x0, unsigned short y0,unsigned short x1, unsigned short y1,unsigned short Color);  
void Gui_box(unsigned short x, unsigned short y, unsigned short w, unsigned short h,unsigned short bc);
void Gui_box2(unsigned short x,unsigned short y,unsigned short w,unsigned short h, unsigned char mode);
void DisplayButtonDown(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void DisplayButtonUp(unsigned short x1,unsigned short y1,unsigned short x2,unsigned short y2);
void Gui_DrawFont_GBK16(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned char *s);
void Gui_DrawFont_GBK24(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned char *s);
void Gui_DrawFont_Num32(unsigned short x, unsigned short y, unsigned short fc, unsigned short bc, unsigned short num) ;



void TFT_SetArea(unsigned short X_Start,unsigned short Y_Start,unsigned short X_End,unsigned short Y_End);
void TFT_ShowImage(const unsigned char *p);
//  TFT 显示字符/汉字/字符串
void TFT_ShowASCII_08x16(unsigned short int X, unsigned short int Y,unsigned char ASCII, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowChinese_16x16(unsigned short int X, unsigned short int Y,unsigned char *Chinese, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowString_16x16(unsigned short int X, unsigned short int Y,unsigned char *String, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowChinese_24x24(unsigned short X, unsigned short Y,unsigned char *Chinese, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
//  TFT 显示有符号整型/无符号整型/浮点型数字
void TFT_ShowNumber_SignedInteger_16x16(unsigned short int X, unsigned short int Y, signed short int IntegerNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowNumber_UnsignedInteger_16x16(unsigned short int X, unsigned short int Y, unsigned short int IntegerNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowNumber_Float_16x16(unsigned short int X, unsigned short int Y, float FloatNumber, unsigned char Count1, unsigned char Count2, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
void TFT_ShowNumber_Binary_16x16(unsigned short int X, unsigned short int Y, unsigned short int BinaryNumber, unsigned char Count, enumTFT_Color FontColor, enumTFT_Color BackgroundColor);
#endif


