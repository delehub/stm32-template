#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

#define LED0 PBout(5)// PB5
#define LED1 PEout(5)// PE5	
#define LED2 PBout(4)// PB5

#define LED_B {LED0=1;LED1=0;LED2=0;}
#define LED_G {LED0=0;LED1=1;LED2=0;}
#define LED_R {LED0=0;LED1=0;LED2=1;}
#define LED_W {LED0=1;LED1=1;LED2=1;}

void LED_Init(void);//≥ı ºªØ

		 				    
#endif
