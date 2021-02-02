/**
************************************************************
* @file         gizwits_product.c
* @brief        Gizwits control protocol processing, and platform-related hardware initialization 
* @author       Gizwits
* @date         2017-07-19
* @version      V03030000
* @copyright    Gizwits
*
* @note         Gizwits is only for smart hardware
*               Gizwits Smart Cloud for Smart Products
*               Links | Value Added | Open | Neutral | Safety | Own | Free | Ecology
*               www.gizwits.com
*
***********************************************************/
#include <stdio.h>
#include <string.h>
#include "gizwits_product.h"
#include "led.h"
#include "usart.h"
static uint32_t timerMsCount;

/** Current datapoint */
dataPoint_t currentDataPoint;


extern unsigned short MQ135_ADC,MQ2_ADC,MQ4_ADC,MQ7_ADC;//ADC采集值
extern float temp1,temp2,temp3,temp4,MQ135_quality,MQ2_quality,MQ4_quality,MQ7_quality,Light; //实际转换值
extern u8 DHT11_Temp,DHT11_Hum;		//温湿度 
/**@} */
/**@name Gizwits User Interface
* @{
*/

/**
* @brief Event handling interface

* Description:

* 1. Users can customize the changes in WiFi module status

* 2. Users can add data points in the function of event processing logic, such as calling the relevant hardware peripherals operating interface

* @param [in] info: event queue
* @param [in] data: protocol data
* @param [in] len: protocol data length
* @return NULL
* @ref gizwits_protocol.h
*/
int8_t gizwitsEventProcess(eventInfo_t *info, uint8_t *gizdata, uint32_t len)
{
  uint8_t i = 0;
  dataPoint_t *dataPointPtr = (dataPoint_t *)gizdata;
  moduleStatusInfo_t *wifiData = (moduleStatusInfo_t *)gizdata;
  protocolTime_t *ptime = (protocolTime_t *)gizdata;
  
#if MODULE_TYPE
  gprsInfo_t *gprsInfoData = (gprsInfo_t *)gizdata;
#else
  moduleInfo_t *ptModuleInfo = (moduleInfo_t *)gizdata;
#endif

  if((NULL == info) || (NULL == gizdata))
  {
    return -1;
  }

  for(i=0; i<info->num; i++)
  {
    switch(info->event[i])
    {
      case EVENT_LED:
        currentDataPoint.valueLED = dataPointPtr->valueLED;
        GIZWITS_LOG("Evt: EVENT_LED %d \n", currentDataPoint.valueLED);
        if(0x01 == currentDataPoint.valueLED)
        {
          //user handle
          LED0=0;
        }
        else
        {
          //user handle
          LED0=1;          
        }
        break;
      case EVENT_Face_Mask:
        currentDataPoint.valueFace_Mask = dataPointPtr->valueFace_Mask;
        GIZWITS_LOG("Evt: EVENT_Face_Mask %d \n", currentDataPoint.valueFace_Mask);
        if(0x01 == currentDataPoint.valueFace_Mask)
        {
          //user handle
          LED1=0;
        }
        else
        {
          //user handle
          LED1=1;
        }
        break;
      case EVENT_Hand:
        currentDataPoint.valueHand = dataPointPtr->valueHand;
        GIZWITS_LOG("Evt: EVENT_Hand %d \n", currentDataPoint.valueHand);
        if(0x01 == currentDataPoint.valueHand)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_Speech:
        currentDataPoint.valueSpeech = dataPointPtr->valueSpeech;
        GIZWITS_LOG("Evt: EVENT_Speech %d \n", currentDataPoint.valueSpeech);
        if(0x01 == currentDataPoint.valueSpeech)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;
      case EVENT_door:
        currentDataPoint.valuedoor = dataPointPtr->valuedoor;
        GIZWITS_LOG("Evt: EVENT_door %d \n", currentDataPoint.valuedoor);
        if(0x01 == currentDataPoint.valuedoor)
        {
          //user handle
        }
        else
        {
          //user handle    
        }
        break;




      case WIFI_SOFTAP:
        break;
      case WIFI_AIRLINK:
        break;
      case WIFI_STATION:
        break;
      case WIFI_CON_ROUTER:
 
        break;
      case WIFI_DISCON_ROUTER:
 
        break;
      case WIFI_CON_M2M:
 
        break;
      case WIFI_DISCON_M2M:
        break;
      case WIFI_RSSI:
        GIZWITS_LOG("RSSI %d\n", wifiData->rssi);
        break;
      case TRANSPARENT_DATA:
        GIZWITS_LOG("TRANSPARENT_DATA \n");
        //user handle , Fetch data from [data] , size is [len]
        break;
      case WIFI_NTP:
        GIZWITS_LOG("WIFI_NTP : [%d-%d-%d %02d:%02d:%02d][%d] \n",ptime->year,ptime->month,ptime->day,ptime->hour,ptime->minute,ptime->second,ptime->ntp);
        break;
      case MODULE_INFO:
            GIZWITS_LOG("MODULE INFO ...\n");
      #if MODULE_TYPE
            GIZWITS_LOG("GPRS MODULE ...\n");
            //Format By gprsInfo_t
      #else
            GIZWITS_LOG("WIF MODULE ...\n");
            //Format By moduleInfo_t
            GIZWITS_LOG("moduleType : [%d] \n",ptModuleInfo->moduleType);
      #endif
    break;
      default:
        break;
    }
  }

  return 0;
}

/**
* User data acquisition

* Here users need to achieve in addition to data points other than the collection of data collection, can be self-defined acquisition frequency and design data filtering algorithm

* @param none
* @return none
*/
void userHandle(void)
{

    currentDataPoint.valueTemp =DHT11_Temp ;//Add Sensor Data Collection
    currentDataPoint.valueHum = DHT11_Hum ;//Add Sensor Data Collection
    currentDataPoint.valueMQ2 = MQ2_quality ;//Add Sensor Data Collection
    currentDataPoint.valueMQ4 =MQ4_quality ;//Add Sensor Data Collection
    currentDataPoint.valueMQ7 = MQ7_quality;//Add Sensor Data Collection
    currentDataPoint.valueMQ135 =MQ135_quality ;//Add Sensor Data Collection
  

  if(LED0==0)
  {
    currentDataPoint.valueLED = 1;
  }
  else
  {
      currentDataPoint.valueLED = 0;
  }
  if(LED1==0)
  {
    currentDataPoint.valueFace_Mask = 1;
  }
  else
  {
     currentDataPoint.valueFace_Mask = 0;
  }
    
}

/**
* Data point initialization function

* In the function to complete the initial user-related data
* @param none
* @return none
* @note The developer can add a data point state initialization value within this function
*/
void userInit(void)
{
    memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));
    
    /** Warning !!! DataPoint Variables Init , Must Within The Data Range **/ 
    /*
      currentDataPoint.valueLED = ;
      currentDataPoint.valueFace_Mask = ;
      currentDataPoint.valueHand = ;
      currentDataPoint.valueSpeech = ;
      currentDataPoint.valuedoor = ;
      currentDataPoint.valueTemp = ;
      currentDataPoint.valueHum = ;
      currentDataPoint.valueMQ2 = ;
      currentDataPoint.valueMQ4 = ;
      currentDataPoint.valueMQ7 = ;
      currentDataPoint.valueMQ135 = ;
    */

}


/**
* @brief  gizTimerMs

* millisecond timer maintenance function ,Millisecond increment , Overflow to zero

* @param none
* @return none
*/
void gizTimerMs(void)
{
    timerMsCount++;
}

/**
* @brief gizGetTimerCount

* Read system time, millisecond timer

* @param none
* @return System time millisecond
*/
uint32_t gizGetTimerCount(void)
{
    return timerMsCount;
}

/**
* @brief mcuRestart

* MCU Reset function

* @param none
* @return none
*/
void mcuRestart(void)
{
    __set_FAULTMASK(1);//关闭所有中断
		NVIC_SystemReset();//复位

}
/**@} */

/**
* @brief TIMER_IRQ_FUN

* Timer Interrupt handler function

* @param none
* @return none
*/
void TIMER_IRQ_FUN(void)
{
  gizTimerMs();
}

/**
* @brief UART_IRQ_FUN

* UART Serial interrupt function ，For Module communication

* Used to receive serial port protocol data between WiFi module

* @param none
* @return none
*/
void UART_IRQ_FUN(void)
{
  uint8_t value = 0;
  //value = USART_ReceiveData(USART2);//STM32 test demo
  gizPutData(&value, 1);
}


/**
* @brief uartWrite

* Serial write operation, send data to the WiFi module

* @param buf      : Data address
* @param len       : Data length
*
* @return : Not 0,Serial send success;
*           -1，Input Param Illegal
*/
int32_t uartWrite(uint8_t *buf, uint32_t len)
{
    uint32_t i = 0;
    
    if(NULL == buf)
    {
        return -1;
    }
    
    #ifdef PROTOCOL_DEBUG
    GIZWITS_LOG("MCU2WiFi[%4d:%4d]: ", gizGetTimerCount(), len);
    for(i=0; i<len; i++)
    {
        GIZWITS_LOG("%02x ", buf[i]);
    }
    GIZWITS_LOG("\n");
    #endif

     for(i=0; i<len; i++)
    {
        USART_SendData(USART3,buf[i]);
        while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕


        if(i >=2 && buf[i] == 0xFF)
        {
						 USART_SendData(USART3,0x55);
          while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕
        }
    }


    
    return len;
}


