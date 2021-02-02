#include "syn6288.h"
#include "USART.H"

void SYN_FrameInfo(u8 Music, u8 *HZdata)
{

  unsigned  char  Frame_Info[50];
  unsigned  char  HZ_Length;
  unsigned  char  ecc  = 0;  		
  unsigned  int i = 0;
  HZ_Length = strlen(HZdata); 		
  Frame_Info[0] = 0xFD ; 		
  Frame_Info[1] = 0x00 ; 		
  Frame_Info[2] = HZ_Length + 3; 		
  Frame_Info[3] = 0x01 ; 		
  Frame_Info[4] = 0x01 | Music << 4 ; 
  for(i = 0; i < 5; i++)   			
  {
    ecc = ecc ^ (Frame_Info[i]);		
  }

  for(i = 0; i < HZ_Length; i++)   		
  {
    ecc = ecc ^ (HZdata[i]); 				
  }
  memcpy(&Frame_Info[5], HZdata, HZ_Length);
  Frame_Info[5 + HZ_Length] = ecc;
  SendString(UART4,Frame_Info, 5 + HZ_Length + 1);
}

void YS_SYN_Set(u8 *Info_data)
{
  u8 Com_Len;
  Com_Len = strlen(Info_data);
  SendString(UART4, Info_data, Com_Len);
}

