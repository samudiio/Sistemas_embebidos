/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"
#include <serial_ctrl.h>
#include <uart.h>
#include <stdio.h>

uint8_t u8100ms_Ctr=0;
uint8_t u8100ms_Ctr2=0;
uint8_t u50ms_ctr = 0;
uint8_t u100ms_ctr = 0;
uint8_t seconds =0;

void Seg_1_Seg(void);
void Seg_4_Seg(void);

uint8_t Ascii_Buffer[] = {'0','0',' '}; 

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

void Seg_1_Seg(void){
	u50ms_ctr++;
	if (u50ms_ctr>=20){
	  u50ms_ctr=0;
	  seconds++;
	//   Uart_SendByte(0,seconds+48); 
			 
	  /* Send de ASCII Value */   
		  if (seconds==10 || seconds==20 || seconds== 30 || seconds==40 || seconds==50){ 
			Ascii_Buffer[0]=(seconds/10)+48; 
			Ascii_Buffer[1]= 48; 
		}  
		else if(seconds==60){//Aqui se puede mandar el else if (seconds==60){manda 00} 
			Ascii_Buffer[0]= 48; 
			Ascii_Buffer[1]= 48; 
		} 
		else{        
			Ascii_Buffer[0]=(seconds/10)+48; 
			Ascii_Buffer[1]= (seconds%10)+48; 
		}        
		
		Uart_SendBuffer(0,&Ascii_Buffer[0],3);    
	  if(seconds>=60){
		  seconds=0;
	  }
	}
}

void vfnTsk_100ms(void)
{ 			
	Seg_4_Seg();
}
void Seg_4_Seg(void){
   uint8_t TxBuffer[] = {"Test Buffer Function ...  Tx\n\r"};
	u100ms_ctr++;
	if (u100ms_ctr>=40){
	  u100ms_ctr=0; 
	  //vfnSerialCtr_Enable_int(0,2,1);
	  Uart_SendBuffer(0,(uint8_t*)&TxBuffer, sizeof(TxBuffer));       
	}
}

