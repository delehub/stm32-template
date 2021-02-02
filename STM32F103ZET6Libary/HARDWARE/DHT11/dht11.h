#ifndef __DHT11_H
#define __DHT11_H

//--------------------------------------------------------------------------------------------------
//  宏自定义声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#define DHT11_IO    GPIOC
#define DHT11_PIN   GPIO_Pin_14
//IO方向设置
#define DHT11_IO_IN()  {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=8<<24;}
#define DHT11_IO_OUT() {DHT11_IO->CRH&=0XF0FFFFFF;DHT11_IO->CRH|=3<<24;}
////IO操作函数											   
#define	DHT11_DQ_OUT PCout(14) //数据端口	PC14 
#define	DHT11_DQ_IN  PCin(14)  //数据端口	PC14 

//--------------------------------------------------------------------------------------------------
//  引用函数声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
unsigned char DHT11_Init(void);//初始化DHT11
unsigned char DHT11_Read_Data(unsigned char *temp,unsigned char *humi);//读取温湿度
unsigned char DHT11_Read_Byte(void);//读出一个字节
unsigned char DHT11_Read_Bit(void);//读出一个位
unsigned char DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11


#endif
















