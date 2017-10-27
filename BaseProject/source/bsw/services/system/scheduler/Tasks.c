/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"


uint8_t u8100ms_Ctr=0;
uint8_t u8100ms_Ctr2=0;
uint8_t u50ms_ctr = 0;
uint8_t u100ms_ctr = 0;
uint8_t seconds =0;


void Seg_1_Seg(void);
void Seg_4_Seg(void);

void vfnTsk_1ms(void)
{
  
}

void vfnTsk_2msA(void)
{
	
}

void vfnTsk_2msB(void)
{
	
}

void vfnTsk_10ms(void)
{
	static uint8_t u8500ms_Ctr=0;
	
	u8500ms_Ctr++;
	
	if (25 <= u8500ms_Ctr)
	{
		u8500ms_Ctr = 0;
		LED_Toggle( 1 );
	}   
}

void vfnTsk_50ms(void)
{
  Seg_1_Seg();  
}

void vfnTsk_100ms(void)
{
  			
  Seg_4_Seg();
}


void Seg_1_Seg(void){

  u50ms_ctr++;
  if (u50ms_ctr>=20){
    u50ms_ctr=0;
    seconds++;
    vfnSerialCtrl_SendSeconds(seconds);        
    if(seconds>=60){
      seconds=0;
    }
  }
}

void Seg_4_Seg(void){

  u100ms_ctr++;
  if (u100ms_ctr>=40){
    u100ms_ctr=0;        
    vfnSerialCtr_Enable_int(0,2,1);
    
  }
}
