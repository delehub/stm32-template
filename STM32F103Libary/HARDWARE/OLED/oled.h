#ifndef __OLED_H
#define __OLED_H	

#include "sys.h"
#include "stdlib.h"	 

#define OLED_MODE 0
#define SIZE 8
#define XLevelL		0x00
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	   

//-----------------OLED IIC端口定义----------------  					   

#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL IIC接口的时钟信号
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SDA IIC接口的数据信号
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)
		     
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据   

//OLED控制用函数
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
//oled 延迟函数
void Delay_50ms(unsigned int Delay_50ms);
void Delay_1ms(unsigned int Delay_1ms);

//IIC控制函数
void IIC_Start(void);
void IIC_Stop(void);
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack(void);

//oled 操作函数
void OLED_Fill(unsigned char fill_Data);//全屏填充
void OLED_Refresh_Gram(void);
void OLED_Set_Pos(unsigned char X, unsigned char Y);
void OLED_AreaClear(unsigned char X, unsigned char Y, unsigned char X_Size, unsigned char Y_Size);

//  OLED 显示字符、字符串
void OLED_ShowChar_06x08(unsigned char X, unsigned char Y, unsigned char Char);
void OLED_ShowString_06x08(unsigned char X, unsigned char Y, unsigned char *String);

void OLED_ShowCHinese(unsigned char X,unsigned char Y,unsigned char Chinese);//显示汉字函数

void OLED_ShowChar_08x16(unsigned char X, unsigned char Y, unsigned char Char);
//void OLED_ShowChinese_16x16(unsigned char X, unsigned char Y, unsigned char *Chinese);
void OLED_ShowString_16x16(unsigned char X, unsigned char Y, unsigned char *String);

void OLED_ShowArray_06x08(unsigned char X, unsigned char Y, unsigned char *Array, unsigned char Count);

//  OLED 显示整型数字/浮点型数字/二进制数字/十六进制数字
void OLED_ShowNumber_SignedInteger_06x08(unsigned char X, unsigned char Y, signed short IntegerNumber, unsigned char Count);
void OLED_ShowNumber_UnsignedInteger_06x08(unsigned char X, unsigned char Y, unsigned short IntegerNumber, unsigned char Count);
void OLED_ShowNumber_Float_06x08(unsigned char X, unsigned char Y, float FloatNumber, unsigned char Count1, unsigned char Count2);
void OLED_ShowNumber_Binary_06x08(unsigned char X, unsigned char Y, unsigned long BinaryNumber, unsigned char Count);
void OLED_ShowNumber_Hex_06x08(unsigned char X, unsigned char Y, unsigned long BinaryNumber, unsigned char Count);

//  OLED 绘制直线
void OLED_DrawLine(unsigned char X, unsigned char Y, unsigned char PointData);

//  OLED 绘制图像
void OLED_RollDisplay(void);//设置水平左右移
void Draw_BMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);


void OLED_DrawDot(unsigned char X,unsigned char Y,unsigned char T);//画点函数
void LCD_DrawLine(unsigned int X1, unsigned int Y1, unsigned int X2,unsigned int Y2);//画直线函数
void OLED_Fill_Draw_circle(unsigned char X0,unsigned char Y0,unsigned char r,unsigned char dot);//dot ==1 表示亮显示出来
void OLED_DrawCircle( uint16_t usX_Center, uint16_t usY_Center, uint16_t usRadius, uint8_t ucFilled );//ucFilled ==1 表示填充 //画直圆函数
void LCD_DrawRectangle(unsigned short X1, unsigned short Y1, unsigned short X2, unsigned short Y2);//矩形
#endif  
