//--------------------------------------------------------------------------------------------------
//  包含的头文件    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#include "RC522.H"                                   // RC522-非接触式读卡器	
#include "delay.h"
#include "stdio.h"
#include <string.h>
//--------------------------------------------------------------------------------------------------
// 宏自定义声明     |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  定义引用变量    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  RC522 引脚操作
#define RC522_RST_OL			GPIO_ResetBits(RC522_RST_OUT,RC522_RST_PIN)					// RC522 RST引脚 输出低电平 数字0				 
#define RC522_RST_OH			GPIO_SetBits(  RC522_RST_OUT,RC522_RST_PIN)					// RC522 RST引脚 输出高电平 数字1   

#define RC522_CSN_OL			GPIO_ResetBits(RC522_SPI_CSN_OUT,RC522_SPI_CSN_PIN)			// RC522 CSN引脚 输出低电平 数字0				 
#define RC522_CSN_OH			GPIO_SetBits(  RC522_SPI_CSN_OUT,RC522_SPI_CSN_PIN)			// RC522 CSN引脚 输出高电平 数字1				    
 
#define RC522_SCK_OL			GPIO_ResetBits(RC522_SPI_SCK_OUT,RC522_SPI_SCK_PIN)			// RC522 SCK引脚 输出低电平 数字0				 
#define RC522_SCK_OH			GPIO_SetBits(  RC522_SPI_SCK_OUT,RC522_SPI_SCK_PIN)			// RC522 SCK引脚 输出高电平 数字1  

#define RC522_SDO_OL			GPIO_ResetBits(RC522_SPI_SDO_OUT,RC522_SPI_SDO_PIN)			// RC522 SDO引脚 输出低电平 数字0				 
#define RC522_SDO_OH			GPIO_SetBits(  RC522_SPI_SDO_OUT,RC522_SPI_SDO_PIN)			// RC522 SDO引脚 输出高电平 数字1 

#define RC522_SDO_IN			GPIO_ReadInputDataBit(RC522_SPI_SDI_OUT,RC522_SPI_SDI_PIN)	// RC522 SDI引脚 输入值

//==============================宏自定义声明========================================================
//  RC522 设备命令 (PCD)
#define RC522_PCD_IDLE 			0x00		// RC522 取消当前命令
#define RC522_PCD_AUTHENT		0x0E		// RC522 验证密钥
#define RC522_PCD_RECEIVE		0x08		// RC522 接收数据
#define RC522_PCD_TRANSMIT		0x04		// RC522 发送数据
#define RC522_PCD_TRANSCEIVE	0x0C		// RC522 发送并接收数据
#define RC522_PCD_RESETPHASE    0x0F		// RC522 设备复位命令
#define RC522_PCD_CALCCRC		0x03		// RC522 CRC计算

//  RC522 卡片命令 (PICC)
#define RC522_PICC_REQIDL		0x26		// RC522 寻天线区内未进入休眠状态
#define RC522_PICC_REQALL		0x52		// RC522 寻天线区内全部卡
#define RC522_PICC_ANTICOLL1	0x93		// RC522 防冲撞
#define RC522_PICC_ANTICOLL2	0x95		// RC522 防冲撞
#define RC522_PICC_AUTHENT1A	0x60		// RC522 验证A密钥
#define RC522_PICC_AUTHENT1B	0x61		// RC522 验证B密钥
#define RC522_PICC_READ			0x30		// RC522 读块
#define RC522_PICC_WRITE		0xA0		// RC522 写块
#define RC522_PICC_DECREMENT	0xC0		// RC522 扣款
#define RC522_PICC_INCREMENT	0xC1		// RC522 充值
#define RC522_PICC_RESTORE		0xC2		// RC522 调块数据到缓冲区
#define RC522_PICC_TRANSFER		0xB0		// RC522 保存缓冲区中数据
#define RC522_PICC_HALT			0x50		// RC522 卡片休眠命令  

//  RC522 寄存器地址
//  (Page 0)命令与状态
#define RC522_REGT_RFU00		0x00		// RC522 寄存器地址，保留
#define RC522_REGT_COMMAND		0x01		// RC522 寄存器地址，启动和停止命令寄存器
#define RC522_REGT_COMIEN		0x02		// RC522 寄存器地址，中断请求传递的使能和禁能控制位
#define RC522_REGT_DIVIEN		0x03		// RC522 寄存器地址，中断请求传递的使能和禁能控制位
#define RC522_REGT_COMIRQ		0x04		// RC522 寄存器地址，包含中断请求标志
#define RC522_REGT_DIVIRQ		0x05		// RC522 寄存器地址，包含中断请求标志
#define RC522_REGT_ERROR		0x06		// RC522 寄存器地址，错误标志，指示执行的上下命令的错误状态
#define RC522_REGT_STATUS1		0x07		// RC522 寄存器地址，包含通信的状态标志
#define RC522_REGT_STATUS2		0x08		// RC522 寄存器地址，包含接收器和发送器的状态标志
#define RC522_REGT_FIFODTATA	0x09		// RC522 寄存器地址，64字节FIFO缓冲区的输入和输出
#define RC522_REGT_FIFOLEVEL	0x0A		// RC522 寄存器地址，指示FIFO中存储的字节数
#define RC522_REGT_WATERLEVEL	0x0B		// RC522 寄存器地址，定义FIFO下溢和上溢报警的FIFO深度
#define RC522_REGT_CONTROL		0x0C		// RC522 寄存器地址，不同的控制寄存器
#define RC522_REGT_BITFRAMING	0x0D		// RC522 寄存器地址，面向位的帧的调节
#define RC522_REGT_COLL			0x0E		// RC522 寄存器地址，RF接口上检测到的第一位冲突的位的位置
#define RC522_REGT_RFU0F		0x0F		// RC522 寄存器地址，保留

//  (Page 1)通信
#define RC522_REGT_RFU10		0x10		// RC522 寄存器地址，保留   
#define RC522_REGT_MODE			0x11		// RC522 寄存器地址，发送和接收模式寄存器
														// 7:6 RFU		 00  RFU 保留
											// 5   TxWait    1   R/W r若RF场产生，则置位
											// 4   RFU		 1   RFU 保留
											// 3   PolSigin  1   R/W SIGIN管脚极性，默认高电平有效
											// 2   RFU		 1   RFU 保留
											// 1:0 CRCPreset 11  R/W CalCRC命令的预设值 00-0000、01-6363、10-A671、11-FFFF
#define RC522_REGT_TXMODE		0x12		// RC522 寄存器地址，定义发送过程中的数据传输速率
#define RC522_REGT_RXMODE		0x13		// RC522 寄存器地址，定义接收过程中的数据传输速率
#define RC522_REGT_TxCONTROL	0x14		// RC522 寄存器地址，控制天线驱动器管脚Tx1和Tx2的逻辑操作
											// 7 InvTX2RFOn  1   R/W
											// 6 InvTX1RFOn  0   R/W 
											// 5 InvTX2RFOff 0   R/W 
											// 4 InvTX1RFOff 0   R/W  
											// 3 Tx2CW		 0   R/W  
											// 2 RFU		   0   RFU 保留 
											// 1 Tx2RFEn     0   R/W 该位置位，TX2管脚输出13.56MHz的能量载波信号  
											// 0 Tx1RFEn     0   R/W 该位置位，TX1管脚输出13.56MHz的能量载波信号   
#define RC522_REGT_TXAUTO		0x15		// RC522 寄存器地址，控制天线驱动器的设置
#define RC522_REGT_TXSEL		0x16		// RC522 寄存器地址，选择模拟部分的内部源
#define RC522_REGT_RXSEL		0x17		// RC522 寄存器地址，选择内部接收器装置
#define RC522_REGT_RXTHRESHOLD  0x18		// RC522 寄存器地址，选择位码器的阈值
#define RC522_REGT_DEMOD		0x19		// RC522 寄存器地址，定义调节器的设置
#define RC522_REGT_RFU1A		0x1A		// RC522 寄存器地址，保留
#define RC522_REGT_RFU1B		0x1B		// RC522 寄存器地址，保留
#define RC522_REGT_MIFARE		0x1C		// RC522 寄存器地址，控制ISO14443/MIFARE模式中 106Kbit/s的通信
#define RC522_REGT_RFU1D		0x1D		// RC522 寄存器地址，保留
#define RC522_REGT_RFU1E		0x1E		// RC522 寄存器地址，保留
#define RC522_REGT_SERIALSPEED  0x1F		// RC522 寄存器地址，选择串行UART接口的速率

//  (Page 2)配置
#define RC522_REGT_RFU20		0x20		// RC522 寄存器地址，保留
#define RC522_REGT_CRCRESULT21  0x21		// RC522 寄存器地址，显示CRC计算的实际MSB和MLB值
#define RC522_REGT_CRCRESULT22  0x22		// RC522 寄存器地址，显示CRC计算的实际MSB和MLB值
#define RC522_REGT_RFU23		0x23		// RC522 寄存器地址，保留
#define RC522_REGT_MODWIDTH     0x24		// RC522 寄存器地址，控制MODWIDTH的设置
#define RC522_REGT_RFU25		0x25		// RC522 寄存器地址，保留
#define RC522_REGT_RFCfg		0x26		// RC522 寄存器地址，控制调制宽度设置
#define RC522_REGT_GSN		    0x27		// RC522 寄存器地址，选择天线驱动器管脚TX1和TX2的调制电导
#define RC522_REGT_CWGSCCfg     0x28		// RC522 寄存器地址，选择天线驱动器管脚TX1和TX2的调制电导
#define RC522_REGT_MODGSCfg     0x29		// RC522 寄存器地址，选择天线驱动器管脚TX1和TX2的调制电导
#define RC522_REGT_TMODE		0x2A		// RC522 寄存器地址，16位内部定时器的设置 
#define RC522_REGT_TPRESCALER   0x2B		// RC522 寄存器地址，16位内部定时器的设置
#define RC522_REGT_TRELOADH     0x2C		// RC522 寄存器地址，16位内部定时器重装值，高位
#define RC522_REGT_TRELOADL     0x2D		// RC522 寄存器地址，16位内部定时器重装值，低位
#define RC522_REGT_TCOUNTER2E   0x2E		// RC522 寄存器地址，16位内部实际定时器值
#define RC522_REGT_TCOUNTER2F   0x2F		// RC522 寄存器地址，16位内部实际定时器值

//  (Page 3)测试
#define RC522_REGT_RFU30		0x30		// RC522 寄存器地址，保留
#define RC522_REGT_TESTSEL1     0x31		// RC522 寄存器地址，常用测试信号的配置
#define RC522_REGT_TESTSEL2     0x32		// RC522 寄存器地址，常用测试信号的配置和PRBS控制
#define RC522_REGT_TESTPINEN    0x33		// RC522 寄存器地址，D1 - D7 输出驱动器的使能管脚(注释 ：仅用于串行接口)
#define RC522_REGT_TESTPINVALUE 0x34		// RC522 寄存器地址，定义D1- D7 用做I/O总线时的值
#define RC522_REGT_TESTBUS		0x35		// RC522 寄存器地址，显示内部测试总线的状态
#define RC522_REGT_AUTOTEST     0x36		// RC522 寄存器地址，控制数字自测试
#define RC522_REGT_VERSION		0x37		// RC522 寄存器地址，显示版本
#define RC522_REGT_ANALOGTEST   0x38		// RC522 寄存器地址，控制管脚AUX1和AUX2
#define RC522_REGT_TESTDAC1     0x39		// RC522 寄存器地址，定义TESTDAC1的测试值
#define RC522_REGT_TESTDAC2     0x3A		// RC522 寄存器地址，定义TESTDAC2的测试值
#define RC522_REGT_TESTDAC		0x3B		// RC522 寄存器地址，显示ADC I和Q通道的测量值
#define RC522_REGT_RFT3C		0x3C		// RC522 寄存器地址，保留用于测试
#define RC522_REGT_RFT3D		0x3D		// RC522 寄存器地址，保留用于测试
#define RC522_REGT_RFT3E		0x3E		// RC522 寄存器地址，保留用于测试
#define RC522_REGT_RFT3F		0x3F		// RC522 寄存器地址，保留用于测试

//  RC522 FIFO相关
#define RC522_FIFO_LENGTH		64			// FIFO(先进先出的数据缓存器) size=64byte
#define RC522_MAXRLEN			18


//  RC522状态代码
#define RC522_NOTAGER		    2
#define RC522_SUCCESS		    1			// 返回值状态成功
#define RC522_FAILURE		    0			// 返回值状态错误

//  RC522错误代码
#define RC522_ERROR_NONE			0x00	// 正常
#define RC522_ERROR_NOMONEY			0x01	// 余额不足
#define RC522_ERROR_NOCMD			0x02	// 无效命令
#define RC522_ERROR_CHECK			0x03	// 校验错误
#define RC522_ERROR_KEYA_IC 		0x04	// 密码错误
#define RC522_ERROR_READ_IC  		0x05	// 读卡失败
#define RC522_ERROR_WRITE_IC  		0x06	// 写卡失败
#define RC522_ERROR_WRITE_KEY_IC	0x07	// 修改密码失败
#define RC522_ERROR_SET_CSTSN		0x08	// 设置客户编码失败
#define RC522_ERROR_NOCARD			0x09	// IC卡不存在
#define RC522_ERROR_ATCLL			0x0A	// 防冲突失败
#define RC522_ERROR_SLCT			0x0B	// 选卡失败
#define RC522_ERROR_BLOCK_ADDR		0x0C	// 块错误
#define RC522_ERROR_OP_TYPE			0x0D	// 操作方式错误		


//--------------------------------------------------------------------------------------------------
//  硬件端口定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  引用函数声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------




//==================================================================================================
//  函数功能：RC522 GPIO 初始化 
//  函数标记：底层函数，修改，
//  函数说明：注意模块时钟设置
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
void RC522_GPIO_Init(void)
{
	//----------------------------------------------------------------------------------------------
	// 定义GPIO结构体类型变量
	//----------------------------------------------------------------------------------------------
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	//----------------------------------------------------------------------------------------------
	// RST引脚操作
	//----------------------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RC522_RST_CLK, ENABLE);		// 打开模块时钟
	
	GPIO_InitStructure.GPIO_Pin   = RC522_RST_PIN;		// 定义端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 定义端口速率
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	// 定义端口类型，推挽输出
	
	GPIO_Init(RC522_RST_OUT, &GPIO_InitStructure);		// 初始化结构体
	
	//----------------------------------------------------------------------------------------------
	// CSN引脚操作
	//----------------------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RC522_SPI_CSN_CLK, ENABLE);	// 打开模块时钟
	
	GPIO_InitStructure.GPIO_Pin   = RC522_SPI_CSN_PIN;	// 定义端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 定义端口速率
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	// 定义端口类型，推挽输出
	
	GPIO_Init(RC522_SPI_CSN_OUT, &GPIO_InitStructure);	// 初始化结构体
	
	//----------------------------------------------------------------------------------------------
	// SCK引脚操作
	//----------------------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RC522_SPI_SCK_CLK, ENABLE);	// 打开模块时钟
	
	GPIO_InitStructure.GPIO_Pin   = RC522_SPI_SCK_PIN;	// 定义端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 定义端口速率
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	// 定义端口类型，推挽输出
	
	GPIO_Init(RC522_SPI_SCK_OUT, &GPIO_InitStructure);	// 初始化结构体
	
	//----------------------------------------------------------------------------------------------
	// SDO引脚操作
	//----------------------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RC522_SPI_SDO_CLK, ENABLE);	// 打开模块时钟
	
	GPIO_InitStructure.GPIO_Pin   = RC522_SPI_SDO_PIN;	// 定义端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 定义端口速率
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;	// 定义端口类型，推挽输出
	
	GPIO_Init(RC522_SPI_SDO_OUT, &GPIO_InitStructure);	// 初始化结构体
	
	//----------------------------------------------------------------------------------------------
	// SDI引脚操作
	//----------------------------------------------------------------------------------------------
	RCC_APB2PeriphClockCmd(RC522_SPI_SDI_CLK, ENABLE);	// 打开模块时钟
	
	GPIO_InitStructure.GPIO_Pin   = RC522_SPI_SDI_PIN;	// 定义端口
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	// 定义端口速率
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;		// 定义端口类型，上拉输入
	
	GPIO_Init(RC522_SPI_SDI_OUT, &GPIO_InitStructure);	// 初始化结构体
}


//==================================================================================================
//  函数功能：RC522 SPI总线 发送1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：软件模拟SPI总线，
//				时钟线 上升沿发送数据，下降沿接收数据。
//				数据线 先发送高位，后发送低位
//--------------------------------------------------------------------------------------------------
//  输入参量：_BYTE - 发送字节；取值范围 - 1个字节。
//  输出参量：无
//==================================================================================================
void RC522_SPI_SendByte(unsigned char _BYTE)
{
	unsigned char i;			// 定义局部变量，用于函数计数循环   
	for(i=0;i<8;i++)			// 循环8次
	{
		if(_BYTE & 0x80) 		// 判断对应数据位 高低电平
			RC522_SDO_OH;		// SDO引脚高电平
		else
			RC522_SDO_OL;		// SDO引脚低电平
		
		_BYTE<<=1;				// 数据左移一位
					
		RC522_SCK_OL;			// SCK引脚高电平
		delay_us(5);			// 延迟一段时间
		RC522_SCK_OH;			// SCK引脚低电平，下降沿写入
		delay_us(5);			// 延迟一段时间
	}		    	
}  

//==================================================================================================
//  函数功能：RC522 SPI总线 接收1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：软件模拟SPI总线，
//				时钟线 上升沿发送数据，下降沿接收数据。
//				数据线 先发送高位，后发送低位
//--------------------------------------------------------------------------------------------------
//  输入参量：
//  输出参量：_BYTE - 发送字节；取值范围 - 1个字节。
//==================================================================================================
unsigned char RC522_SPI_RecvByte(void)
{
	unsigned char i;			// 定义局部变量，用于函数计数循环
	unsigned char Retu = 0;	// 定义局部变量，用于函数数值返回

	for(i=0;i<8;i++)			// 循环8次
	{
		Retu<<=1;				// 数据左移一位
		RC522_SCK_OL;			// SCK引脚低电平
		delay_us(5);			// 延迟一段时间
		if(RC522_SDO_IN)		// SDO引脚判断是否有输入信号
		{
			Retu|=0x01;
		}
		RC522_SCK_OH;			// SCK引脚高电平
		delay_us(5);			// 延迟一段时间
	}										 
	return (Retu);
}

//==================================================================================================
//  函数功能：RC522 读取寄存器 1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：第 0 位 默认为0
//				第1~6位 具体地址
//				第 7 位 设置1为读寄存器 设置0为写寄存器
//				地址先发送高位，即第 7 位
//--------------------------------------------------------------------------------------------------
//  输入参量：_REGT - 寄存器地址；取值范围 - RC522寄存器地址。
//  输出参量：_RETU - 寄存器内容；取值范围 - 1个字节。
//==================================================================================================
unsigned char RC522_ReadByte_Regt(unsigned char _REGT)
{
	unsigned char _RETU;								// 定义局部变量，用于函数返回

	RC522_CSN_OL;										// 片选使能有效，开始SPI总线

		    RC522_SPI_SendByte(((_REGT<<1)&0x7E)|0x80);// 写入寄存器地址
	_RETU=RC522_SPI_RecvByte();							// 读取寄存器数值

	RC522_CSN_OH;										// 片选使能无效，终止SPI总线
	
	return(_RETU);				
}

//==================================================================================================
//  函数功能：RC522 写入寄存器 1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：第 0 位 默认为0
//				第1~6位 具体地址
//				第 7 位 设置1为读寄存器 设置0为写寄存器
//				地址先发送高位，即第 7 位
//--------------------------------------------------------------------------------------------------
//  输入参量：_REGT - 寄存器地址；取值范围 - RC522寄存器地址。
//				_DATA - 寄存器内容；取值范围 - 1个字节。
//  输出参量：无
//==================================================================================================
void RC522_WrteByte_Regt(unsigned char _REGT,unsigned char _DATA)
{
	RC522_CSN_OL;							// 片选使能有效，开始SPI总线

	RC522_SPI_SendByte((_REGT<<1)&0x7E);	// 写入寄存器地址
	RC522_SPI_SendByte(_DATA);				// 写入寄存器数值

	RC522_CSN_OH;							// 片选使能无效，终止SPI总线
}

//==================================================================================================
//  函数功能：RC522 置位寄存器 1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：掩码对应位，置1操作
//--------------------------------------------------------------------------------------------------
//  输入参量：_REGT - 寄存器地址；取值范围 - RC522寄存器地址。
//				_MASK - 寄存器掩码；取值范围 - 1个字节。
//  输出参量：无
//==================================================================================================
void RC522_SetsMask_Regt(unsigned char _REGT,unsigned char _MASK)
{
	unsigned char Temp = 0x00;				// 定义局部变量，用于数据临时存储
	Temp=RC522_ReadByte_Regt(_REGT);			// 读取寄存器原始数据
	RC522_WrteByte_Regt(_REGT,Temp | _MASK);	// 写入寄存器新的数据	
}

//==================================================================================================
//  函数功能：RC522 清位寄存器 1个字节  
//  函数标记：底层函数，待完善，
//  函数说明：掩码对应位，清0操作
//--------------------------------------------------------------------------------------------------
//  输入参量：_REGT - 寄存器地址；取值范围 - RC522寄存器地址。
//				_MASK - 寄存器掩码；取值范围 - 1个字节。
//  输出参量：无
//==================================================================================================
void RC522_ClerMask_Regt(unsigned char _REGT,unsigned char _MASK)
{
	unsigned char Temp=0x00;					// 定义局部变量，用于数据临时存储
	Temp=RC522_ReadByte_Regt(_REGT);			// 读取寄存器原始数据
	RC522_WrteByte_Regt(_REGT,Temp&(~_MASK));	// 写入寄存器新的数据	
}

//==================================================================================================
//  函数功能：RC522 天线开启  
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
void RCC522_AnteOpen(void)
{
	unsigned char Temp;		// 定义局部变量，用于临时存储

	Temp=RC522_ReadByte_Regt(RC522_REGT_TxCONTROL);
	if(!(Temp&0x03))
	{
		RC522_SetsMask_Regt(RC522_REGT_TxCONTROL,0x03);
	}
}

//==================================================================================================
//  函数功能：RC522 天线关闭  
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
void RCC522_AnteClse(void)
{
	RC522_ClerMask_Regt(RC522_REGT_TxCONTROL,0x03);
}

//==================================================================================================
//  函数功能：RC522 设置协议 
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：_TYPE - 协议类型；取值范围 - 'A' 表示	ISO14443_A 协议
//  输出参量：无
//==================================================================================================
void RCC522_SetsAgre(unsigned char _TYPE)
{
	switch(_TYPE)
	{
		case 'A':		// ISO14443_A 协议
		{
			RC522_ClerMask_Regt(RC522_REGT_STATUS2,   0x08);	// 设置状态
			RC522_WrteByte_Regt(RC522_REGT_MODE,		0x3D);	// 通讯时，CRC初始值0x6363

			RC522_WrteByte_Regt(RC522_REGT_RXSEL,     0x86);
			RC522_WrteByte_Regt(RC522_REGT_RFCfg,     0x7F);  

			RC522_WrteByte_Regt(RC522_REGT_TRELOADL,    30);	// 设置定时器长度		     
			RC522_WrteByte_Regt(RC522_REGT_TRELOADH,     0);
			
			RC522_WrteByte_Regt(RC522_REGT_TMODE,     0x8D);	// 设置定时器方式
			RC522_WrteByte_Regt(RC522_REGT_TPRESCALER,0x3E);
			delay_ms(10);										// 延迟10ms	

		}break;
		default:		// 其他协议		
		{
			
		}break;
	}		
}

//==================================================================================================
//  函数功能：RC522 计算CRC16 协处理器
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：_WrteData - 待写字符串；取值范围 - 通过RC522写入到卡片的数据
//            _Leth     - 待写长度  ；取值范围 - 0 ~ 18
//            _ReadData - 待写字符串；取值范围 - 通过RC522读到到卡片的数据  
//  输出参量：无
//==================================================================================================
void RC522_Calu_Crc(unsigned char *_WrteData,unsigned char _Leth,unsigned char *_ReadData)
{
	unsigned char i;											// 定义局部变量，用于函数计数循环
	unsigned char Temp=0x00;									// 定义局部变量，用于函数临时存储
	RC522_ClerMask_Regt(RC522_REGT_DIVIRQ,0x04);				// 清除中断标志位
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,RC522_PCD_IDLE);		// 在启动和停止命令寄存器取消当前命令
	RC522_SetsMask_Regt(RC522_REGT_FIFOLEVEL,0x80);				// 在指示FIFO中存储字节

	for(i=0;i < _Leth;i++)
	{
		RC522_WrteByte_Regt(RC522_REGT_FIFODTATA,*(_WrteData+i));	//将字符串写入指令中	
	}
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,RC522_PCD_CALCCRC);		//计算CRC
	i=0xFF;
    do 
    {
		  Temp=RC522_ReadByte_Regt(RC522_REGT_DIVIRQ);				//读中断请求寄存器的字节
		  i--;
    }
    while ((i!=0) && !(Temp&0x04));
	_ReadData[0]=RC522_ReadByte_Regt(RC522_REGT_CRCRESULT22);		//显示CRC计算的实际MLB值
	_ReadData[1]=RC522_ReadByte_Regt(RC522_REGT_CRCRESULT21);		//显示CRC计算的实际MSB值
}

//==================================================================================================
//  函数功能：RC522 与 ISO14443卡通信
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：_Comd  - RC522命令字节			；取值范围 - RC522命令字
//            _WrteData - 待写字符串			；取值范围 - 通过RC522写入到卡片的数据
//            _WrteCunt - 待写发送数据字节长度  ；取值范围 - 发送数据的字节长度
//            _ReadData - 待写字符串			；取值范围 - 接收到的卡片返回数据 
//            _ReadCunt - 待写接收数据的位长度  ；取值范围 - 返回数据的位长度
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_CommCard(unsigned char  _Comd,
										unsigned char *_WrteData, 
										unsigned char  _WrteCunt,
										unsigned char *_ReadData,
										unsigned int  *_ReadCunt)
{
	unsigned char Retu = RC522_FAILURE;		// 定义局部变量，用于函数数值返回
	unsigned char IRQ_EN=0x00;					// 定义局部变量，用于临时存储
	unsigned char WAIT_FOR=0x00;				// 定义局部变量，用于临时存储
	unsigned char LastBit;						// 定义局部变量，用于最后一位
	unsigned char Temp=0x00;					// 定义局部变量，用于临时存储字节数
	unsigned int i;								// 定义局部变量，用于计数循环
    
	// 判断命令类型
	switch (_Comd)
    {
		  case RC522_PCD_AUTHENT:					// 验证命令 
		{									
			IRQ_EN   = 0x12;
			WAIT_FOR = 0x10;
		}break;
		case RC522_PCD_TRANSCEIVE:				// 发送并接收数据
		{
			IRQ_EN   = 0x77;
			WAIT_FOR = 0x30;
		}break;			
		default:
		{
			
		}break;
    }
	
	RC522_WrteByte_Regt(RC522_REGT_COMIEN,IRQ_EN|0x80);				// 写入中断请求
	RC522_ClerMask_Regt(RC522_REGT_COMIRQ,0x80);					// 擦除中断请求
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,RC522_PCD_IDLE);			// 将取消当前命令写入寄存器
	RC522_SetsMask_Regt(RC522_REGT_FIFOLEVEL,0x80);					// 擦除FIFO中存储的字节数
    
	for(i=0; i < _WrteCunt; i++)									// 写入的长度
    {   
		RC522_WrteByte_Regt(RC522_REGT_FIFODTATA, _WrteData[i]);    // 写入64字节FIFO缓冲区
	}
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,_Comd);						// 写入命令寄存器

	if( _Comd == RC522_PCD_TRANSCEIVE)								// 判断发送数据
    {    
		RC522_SetsMask_Regt(RC522_REGT_BITFRAMING,0x80);  			// 置位面向位的帧寄存器
	}
	
	// 根据时钟频率调整，操作M1卡最大等待时间25ms
	i = 2000;
    do 
    {
		  Temp = RC522_ReadByte_Regt(RC522_REGT_COMIRQ);				// 读取中断请求标志的字节
		  i--;
    }
    while ((i!=0) && !(Temp&0x01) && !(Temp&WAIT_FOR));
	RC522_ClerMask_Regt(RC522_REGT_BITFRAMING,0x80);				// 清除面向位的帧	
	
    if (i!=0)		// 判断i未到0的时刻
    {    
		if(!(RC522_ReadByte_Regt(RC522_REGT_ERROR)&0x1B))	// 读取错误标志并进行判断
		{
			Retu = RC522_SUCCESS;							// 表示正确
			if (Temp & IRQ_EN & 0x01)
			{  
				Retu = RC522_NOTAGER;   
			}
			if ( _Comd == RC522_PCD_TRANSCEIVE)
			{
				Temp = RC522_ReadByte_Regt(RC522_REGT_FIFOLEVEL);	//读取指示FIFO中存储的字节数
				LastBit = RC522_ReadByte_Regt(RC522_REGT_CONTROL) & 0x07;
				if(LastBit)					// 判断是否为最后一位
				{   
					*_ReadCunt = (Temp-1)*8 + LastBit;		// 读出卡片的数据的长度   
				}
				else
				{   
					*_ReadCunt = Temp*8;   
				}
				// 	让 存储字节数控制在1 ~ 18
				if(Temp == 0)
				{   
					Temp = 1;    
				}
				if(Temp > RC522_MAXRLEN)
				{   
					Temp = RC522_MAXRLEN;   
				}
				for(i=0; i<Temp; i++)
				{   
					_ReadData[i] = RC522_ReadByte_Regt(RC522_REGT_FIFODTATA); // 读FIFO缓冲区到卡片的数据    
				}
			}
		}
		else
		{   
			Retu = RC522_FAILURE;   
		}
		  
    }
	RC522_SetsMask_Regt(RC522_REGT_CONTROL,0x80);			// 置位不同的控制位
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,RC522_PCD_IDLE);	// 取消当前命令 
	return Retu;
}


//==================================================================================================
//  函数功能：RC522 寻卡
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：_MODE - 寻卡方式；取值范围：0x52 - 寻感应区内所有符合14443A标准的卡
//                                        0x26 = 寻未进入休眠状态的卡
//           _TYPE - 本卡类型；取值范围：0x4400 = Mifare_UltraLight
//                                       0x0400 = Mifare_One(S50)
//                                       0x0200 = Mifare_One(S70)
//                                       0x0800 = Mifare_Pro(X)
//                                       0x4403 = Mifare_DESFire 
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_SeekCard(unsigned char _MODE,unsigned char *_TYPE)
{
	unsigned char Retu;								// 定义局部变量，用于函数返回	
	unsigned int  ReadCunt;							// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];			// 定义局部数组，用于临时存储
	
	RC522_ClerMask_Regt(RC522_REGT_STATUS2,   0x08);	// 清位发送与接收寄存器
	RC522_WrteByte_Regt(RC522_REGT_BITFRAMING,0x07);	// 写入面向位的帧的调节寄存器地址
	RC522_SetsMask_Regt(RC522_REGT_TxCONTROL, 0x03);	// 控制天线驱动器

	RC522_Arry[0] = _MODE;								// 确定一个数组的首地址
	
	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,1,RC522_Arry,&(ReadCunt));
	
	// 如果通信成功则执行下条语句
	if((Retu == RC522_SUCCESS) && ( ReadCunt == 0x10))
	{    
		*_TYPE     = RC522_Arry[0];
		*(_TYPE+1) = RC522_Arry[1];
	}
	else
	{   
		Retu = RC522_FAILURE;   
	}
   
	return Retu;		 					// 返回	和RC522通讯时返回的代码
}
//==================================================================================================
//  函数功能：RC522 防冲撞
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：_CARD - 寻卡方式 ；取值范围 -4个字节 
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_SeekEcho(unsigned char *_CARD)
{
	unsigned char Retu;			// 定义局部变量，用于函数返回	
	unsigned char i;				// 定义局部变量，用于计数循环
	unsigned char CARD_Check=0;
	unsigned int  ReadCunt;		// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];		// 定义局部数组，用于临时存储
	
	RC522_ClerMask_Regt(RC522_REGT_STATUS2,0x08);		// 清除发送器的状态标志
	RC522_WrteByte_Regt(RC522_REGT_BITFRAMING,0x00);  	// 重新写入面向位的帧指令
	RC522_ClerMask_Regt(RC522_REGT_COLL,0x80);			// 清除RF接口上检测到的第一位冲突的位的位置

	RC522_Arry[0]=RC522_PICC_ANTICOLL1;				// 将防数组的首地址临时存储冲撞的首地址
	RC522_Arry[1]=0x20;
	
	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,2,RC522_Arry,&ReadCunt);
	
	// 如果通信成功则执行下条语句
    if(Retu == RC522_SUCCESS)
	{
		for (i=0; i<4; i++)
		{   
			*(_CARD+i)  = RC522_Arry[i];
			CARD_Check ^= RC522_Arry[i];
		}
		if(CARD_Check != RC522_Arry[i])
   		{   
			Retu = RC522_FAILURE;    
		}
    }
    
    RC522_SetsMask_Regt(RC522_REGT_COLL,0x80);		// 置位 RF接口上检测到的第一位冲突的位的位置 寄存器
    return Retu;		 							// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 选定卡片
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：_CARD - 寻卡方式 ；取值范围 - 4个字节 
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_SeleCard(unsigned char *_CARD)
{									 	
	unsigned char Retu;							// 定义局部变量，用于函数返回	
	unsigned char i;								// 定义局部变量，用于计数循环
	unsigned int  ReadCunt;						// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];		// 定义局部数组，用于临时存储

	RC522_Arry[0]=RC522_PICC_ANTICOLL1;				// 将防数组的首地址临时存储冲撞的首地址
	RC522_Arry[1]=0x70;
	RC522_Arry[6]=	 0;

	for(i=0; i<4; i++)
	{   
		RC522_Arry[i+2]  =	 *(_CARD+i);
		RC522_Arry[6]   ^=   *(_CARD+i);
	}
	RC522_Calu_Crc(RC522_Arry,7,&RC522_Arry[7]);		// 计算CRC16 协处理器
	RC522_ClerMask_Regt(RC522_REGT_STATUS2,0x08);		// 清除发送器的状态标志
	
	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,9,RC522_Arry,&ReadCunt);
	// 如果通信成功则执行下条语句
    if((Retu == RC522_SUCCESS) && (ReadCunt == 0x18))
    {   
		Retu = RC522_SUCCESS;		//返回值正确信号		
	}
    else
    {   
		Retu = RC522_FAILURE;		//返回值错误信号    
	}
    return Retu;					// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 验证卡片密码
//  函数标记：应用函数，待完善，
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//--------------------------------------------------------------------------------------------------
//  输入参量：_AUTH_MODE  - 密码验证模式 ； 取值范围 
//				     							0x60 = 验证A密钥
//				    							0x61 = 验证B密钥
//				_ADDR[IN]：						 块地址
//				_PKEY[IN]：					密码
//				_PSNR[IN]：- 卡片序列号    :  4字节 
//  输出参量：成功返回RC522_SUCCESS
//================================================================================================== 
signed char RC522_PcdAuthStat(unsigned char _AUTH_MODE,unsigned char _ADDR,unsigned char *_PKEY,unsigned char *_PSNR)
{
	unsigned char Retu;						// 定义局部变量，用于函数返回
	unsigned int _ReadCunt;					// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];	// 定义局部数组，用于临时存储

	RC522_Arry[0] = _AUTH_MODE;					// 密钥验证地址临时存储
	RC522_Arry[1] = _ADDR;
    
	memcpy(&RC522_Arry[2], _PKEY, 6); 
	memcpy(&RC522_Arry[8], _PSNR, 6); 

	// 判断是否与ISO14443卡通信成功
	Retu =  RC522_CommCard(RC522_PCD_AUTHENT,RC522_Arry,12,RC522_Arry,&_ReadCunt);
	// 如果通信成功则执行下条语句
    if((Retu != RC522_SUCCESS) || ( !(RC522_ReadByte_Regt(RC522_REGT_STATUS2) & 0x08)))
    {   
		Retu = RC522_FAILURE;		//返回值错误信号 		
	}
    return Retu;					// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 写入M1卡一块数据
//  函数标记：应用函数，待完善，
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//--------------------------------------------------------------------------------------------------
//  输入参量：_ADDR     - 块地址    ；取值范围 -  0~ 64
//            _WrteData - 待写入字节；取值范围 - 每块支持16字节
//  输出参量：成功返回RC522_SUCCESS

//================================================================================================== 
unsigned char RC522_PCD_WrteData(unsigned char _ADDR,unsigned char *_WrteData)
{
	unsigned char Retu;							// 定义局部变量，用于函数返回	
	unsigned int _ReadCunt;							// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];		// 定义局部数组，用于临时存储

	RC522_Arry[0] = RC522_PICC_WRITE;				// 写块  临时存储
	RC522_Arry[1] = _ADDR;
	RC522_Calu_Crc(RC522_Arry,2,&RC522_Arry[2]);	// 计算CRC16 协处理器

	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,4,RC522_Arry,&_ReadCunt);
	
	// 如果通信成功则执行下条语句
    if((Retu != RC522_SUCCESS) || ((RC522_Arry[0] & 0x0F) != 0x0A) || (_ReadCunt != 4))
    {   
		Retu = RC522_FAILURE;		//返回值错误信号 		
	}
    if(Retu == RC522_SUCCESS)
    {
		memcpy(RC522_Arry, _WrteData, 16);   
		RC522_Calu_Crc(RC522_Arry,16,&RC522_Arry[16]);	// 计算CRC16 协处理器
		// 判断是否与ISO14443卡通信成功
		Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,18,RC522_Arry,&_ReadCunt);
		// 如果通信成功则执行下条语句
		  if((Retu != RC522_SUCCESS) || (_ReadCunt != 4) || ((RC522_Arry[0] & 0x0F) != 0x0A))
		  {   
			Retu = RC522_FAILURE;		//返回值错误信号 		
		}
	}
    return Retu;					// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 读取M1卡一块数据
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：_ADDR     - 块地址    ；取值范围 -  0~ 64
//            _ReadData - 欲读出字节；取值范围 - 每块支持16字节
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//================================================================================================== 
unsigned char RC522_PCD_ReadData(unsigned char _ADDR,unsigned char *_ReadData)
{
	unsigned char Retu;							// 定义局部变量，用于函数返回	
	unsigned int _ReadCunt;							// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];		// 定义局部数组，用于临时存储

	RC522_Arry[0] = RC522_PICC_READ;				// 读块 临时存储
	RC522_Arry[1] = _ADDR;
	RC522_Calu_Crc(RC522_Arry,2,&RC522_Arry[2]);	// 计算CRC16 协处理器

	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,4,RC522_Arry,&_ReadCunt);
	// 如果通信成功则执行下条语句
    if((Retu == RC522_SUCCESS) && (_ReadCunt == 0x90))
    {  
		memcpy(_ReadData, RC522_Arry, 16);  
	}
    else
    {   
		Retu = RC522_FAILURE;		//返回值错误信号    
	}
    return Retu;					// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 IC卡片 休眠状态
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//================================================================================================== 
signed char RC522_Card_Halt(void)
{
	unsigned char Retu;							// 定义局部变量，用于函数返回	
	unsigned int _ReadCunt;						// 定义局部变量，用于接收数据的位长度
	unsigned char RC522_Arry[RC522_MAXRLEN];		// 定义局部数组，用于临时存储

	RC522_Arry[0] = RC522_PICC_HALT;				  	// 卡片休眠命令 临时存储
	RC522_Arry[1] = 0;
	
	RC522_Calu_Crc(RC522_Arry,2,&RC522_Arry[2]);	// 计算CRC16 协处理器

	// 判断是否与ISO14443卡通信成功
	Retu = RC522_CommCard(RC522_PCD_TRANSCEIVE,RC522_Arry,4,RC522_Arry,&_ReadCunt);

    return Retu;					// 返回	和RC522通讯时返回的代码
}

//==================================================================================================
//  函数功能：RC522 初始化  
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
void RC522_Init(void)
{
	//----------------------------------------------------------------------------------------------
	// 端口引脚初始化
	//----------------------------------------------------------------------------------------------
	RC522_GPIO_Init();
	
	//----------------------------------------------------------------------------------------------
	// 硬件复位
	//----------------------------------------------------------------------------------------------
	RC522_RST_OH;			// RST引脚高电平
	delay_us(100);			// 延迟一段时间
	RC522_RST_OL;			// RST引脚低电平
	delay_us(100);			// 延迟一段时间
	RC522_RST_OH;			// RST引脚高电平
	delay_us(100);			// 延迟一段时间
	
	//----------------------------------------------------------------------------------------------
	// 软件复位
	//----------------------------------------------------------------------------------------------
	RC522_WrteByte_Regt(RC522_REGT_COMMAND,RC522_PCD_RESETPHASE); 	// 执行复位命令
	delay_us(100);													// 延迟一段时间
	
	//----------------------------------------------------------------------------------------------
	// 寄存器设置
	//----------------------------------------------------------------------------------------------
	RC522_WrteByte_Regt(RC522_REGT_MODE,0x3D);			// 通讯时，CRC初始值0x6363
	
	RC522_WrteByte_Regt(RC522_REGT_TRELOADL,30);		// 设置定时器长度		     
	RC522_WrteByte_Regt(RC522_REGT_TRELOADH,0);
	
	RC522_WrteByte_Regt(RC522_REGT_TMODE,0x8D);			// 设置定时器方式
	RC522_WrteByte_Regt(RC522_REGT_TPRESCALER,0x3E);
	
	RC522_WrteByte_Regt(RC522_REGT_TXAUTO,0x40);		// 必须要？(数据手册此处用了保留寄存器，需注意)
	
	//----------------------------------------------------------------------------------------------
	// 天线操作
	//----------------------------------------------------------------------------------------------
	RCC522_AnteClse();			// 天线关闭
 	delay_ms(20);				// 延迟一段时间
	RCC522_AnteOpen();			// 天线重新打开
	
	//----------------------------------------------------------------------------------------------
	// 设置协议
	//----------------------------------------------------------------------------------------------
	RCC522_SetsAgre('A');		
}

//==================================================================================================
//  函数功能：RC522 计算密码 
//  函数标记：应用函数，待完善，
//  函数说明：无
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
const unsigned char DefaultKeyABuf[6]     = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
const unsigned char CardKeyABlockBuf[16] = {
											   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 密钥A 
											   0xff, 0x07, 0x80, 0x69,					// 访问条件
											   0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	// 密钥B 
											   
											 };
void calculate_keyA(unsigned char *DestBuf)
{
	const unsigned char KeyABuf[6] = { 0x20, 0x12, 0x10, 0x01, 0x00, 0x00 };
	memcpy( DestBuf, KeyABuf,6);
}



//==================================================================================================
//  函数功能：RC522 获取卡号
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_CradGetsNumb(unsigned char *Buff)
{
	unsigned char i;
	unsigned char Retu = RC522_FAILURE;     // 定义局部变量，用于函数数值返回						
	unsigned char RecvBuff[16]={0};		    // 定义局部指针，用于函数临时存储
	
	//----------------------------------------------------------------------------------------------
	// 检查是否存在未休眠的卡
	// 返回卡片类型 2字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
	{
		if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
		{
			return Retu;
		}	
	}
	
	//----------------------------------------------------------------------------------------------
	// 防冲撞检测
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekEcho( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 读取卡号
	//----------------------------------------------------------------------------------------------
	for(i=0;i<4;i++)
	{
		Buff[i]=RecvBuff[2+i];
	}
	
	return RC522_SUCCESS;
}

//==================================================================================================
//  函数功能：RC522 卡号注册
//  函数标记：应用函数，待完善，
//  函数说明：
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：成功 函数返回 RC522_SUCCESS 
//            失败 函数返回 RC522_FAILURE 
//==================================================================================================
unsigned char RC522_CradRegt(void)
{
	unsigned char Retu = RC522_FAILURE;// 定义局部变量，用于函数数值返回
	unsigned char KeyABuff[ 6];		// 定义局部变量，用于秘钥A解密
	unsigned char RecvBuff[16];		// 定义局部指针，用于函数临时存储
	unsigned char WrteBuff[16];		// 定义局部指针，用于函数临时存储
	
	//----------------------------------------------------------------------------------------------
	// 检查是否存在未休眠的卡
	// 返回卡片类型 2字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
	{
		if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
		{
			return Retu;
		}	
	}
	
	//----------------------------------------------------------------------------------------------
	// 防冲撞检测
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekEcho( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 选定卡
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeleCard( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}

	//----------------------------------------------------------------------------------------------
	// 计算密码
	//----------------------------------------------------------------------------------------------
	calculate_keyA( KeyABuff );

	//----------------------------------------------------------------------------------------------
	// 验证密码
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_PcdAuthStat( RC522_PICC_AUTHENT1A, 4, (unsigned char *)DefaultKeyABuf, &RecvBuff[2] ) != RC522_SUCCESS )
	{
		return Retu;
	}
	memset( WrteBuff,0,16);
	
	//----------------------------------------------------------------------------------------------
	// 写卡
	// 因为射频卡中每块扇区的第四个字节中密钥A + 访问条件 + 密钥B 其中该块中秘钥B无用
	//----------------------------------------------------------------------------------------------
	if( RC522_PCD_WrteData( 4, WrteBuff ) != RC522_SUCCESS )
	{
		return Retu;
	}
					
	memcpy( WrteBuff, CardKeyABlockBuf, 16 );		// 复制 密钥A + 访问条件 + 密钥B
	memcpy( WrteBuff, KeyABuff, 6 );				// 复制 密钥A 
	
	//----------------------------------------------------------------------------------------------
	// 修改密钥内容
	//----------------------------------------------------------------------------------------------
	if( RC522_PCD_WrteData( 7, WrteBuff ) != RC522_SUCCESS )
	{
		return Retu;
	}
	return RC522_SUCCESS;
}

//==================================================================================================
//  函数功能：RC522 卡片 读数据
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
unsigned char RC522_CradReadData(unsigned char _Numb,unsigned long *_Data)
{
	unsigned char Retu = RC522_FAILURE;// 定义局部变量，用于函数数值返回
	unsigned char KeyABuff[ 6];		// 定义局部变量，用于秘钥A解密
	unsigned char RecvBuff[16];		// 定义局部指针，用于函数临时存储
	
	unsigned long Card_Data;
	//----------------------------------------------------------------------------------------------
	// 检查是否存在未休眠的卡
	// 返回卡片类型 2字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
	{
		if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
		{
			return Retu;
		}	
	}
	
	//----------------------------------------------------------------------------------------------
	// 防冲撞检测
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekEcho( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 选定卡
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeleCard( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 计算密码
	//----------------------------------------------------------------------------------------------
	calculate_keyA( KeyABuff );
	
	//----------------------------------------------------------------------------------------------
	// 校验密钥
	//----------------------------------------------------------------------------------------------
	if( RC522_PcdAuthStat( RC522_PICC_AUTHENT1A, 4, KeyABuff, &RecvBuff[2] ) != RC522_SUCCESS )// 验证密码
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 读卡
	//----------------------------------------------------------------------------------------------
	if( RC522_PCD_ReadData( _Numb, RecvBuff ) != RC522_SUCCESS )// 读数据
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 数组转成整型
	//----------------------------------------------------------------------------------------------
	memcpy( ( unsigned char * )&Card_Data, RecvBuff, 4 ); 

	//----------------------------------------------------------------------------------------------
	// 读取数值
	//----------------------------------------------------------------------------------------------
	*_Data = Card_Data ;
	
	return RC522_SUCCESS;
}

//==================================================================================================
//  函数功能：RC522 卡片 写数据
//  函数标记：应用函数，待完善，
//  函数说明：成功返回RC522_SUCCESS
//--------------------------------------------------------------------------------------------------
//  输入参量：无
//  输出参量：无
//==================================================================================================
unsigned char RC522_CradWrteData(unsigned char _Numb,unsigned long *_Data)
{
	unsigned char Retu = RC522_FAILURE;// 定义局部变量，用于函数数值返回
	unsigned char KeyABuff[ 6];		// 定义局部变量，用于秘钥A解密
	unsigned char RecvBuff[16];		// 定义局部指针，用于函数临时存储
	unsigned char WrteBuff[16];		// 定义局部指针，用于函数临时存储
	
	unsigned long Card_Data;
	//----------------------------------------------------------------------------------------------
	// 检查是否存在未休眠的卡
	// 返回卡片类型 2字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
	{
		if( RC522_SeekCard( RC522_PICC_REQIDL, &RecvBuff[0] ) != RC522_SUCCESS )
		{
			return Retu;
		}	
	}
	
	//----------------------------------------------------------------------------------------------
	// 防冲撞检测
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeekEcho( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 选定卡
	// 返回卡的序列号 4字节
	//----------------------------------------------------------------------------------------------
	if( RC522_SeleCard( &RecvBuff[2] ) != RC522_SUCCESS ) 	
	{
		return Retu;
	}
	
	//----------------------------------------------------------------------------------------------
	// 计算密码
	//----------------------------------------------------------------------------------------------
	calculate_keyA( KeyABuff );
	
	//----------------------------------------------------------------------------------------------
	// 校验密钥
	//----------------------------------------------------------------------------------------------
	if( RC522_PcdAuthStat( RC522_PICC_AUTHENT1A, 4, KeyABuff, &RecvBuff[2] ) != RC522_SUCCESS )// 验证密码
	{
		return Retu;
	}

	//----------------------------------------------------------------------------------------------
	// 增加数据
	//----------------------------------------------------------------------------------------------
	Card_Data = *_Data;
	
	//----------------------------------------------------------------------------------------------
	// 数组转成整型
	//----------------------------------------------------------------------------------------------
	memset( WrteBuff, 0, 16 );
	memcpy( WrteBuff, ( unsigned char * )&Card_Data, 4 );
	
	if( RC522_PCD_WrteData( _Numb, WrteBuff ) != RC522_SUCCESS )// 写数据
	{
		return Retu;
	}
	
	return RC522_SUCCESS;
}



