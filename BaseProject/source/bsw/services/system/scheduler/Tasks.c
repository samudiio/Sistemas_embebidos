/*
 * Tasks.c
 *
 * Created: 6/21/2016 7:25:43 PM
 *  Author: Francisco Martinez
 */ 

#include "Tasks.h"
#include "led.h"
#include <uart.h>
#include <stdio.h>

uint8_t u8100ms_Ctr=0;
uint8_t u8100ms_Ctr2=0;


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
	// static uint8_t u8500ms_Ctr=0;
	
	// u8500ms_Ctr++;
	
	// if (25 <= u8500ms_Ctr)
	// {
	// 	u8500ms_Ctr = 0;
	// 	LED_Toggle( 1 );
	// }   
}

void vfnTsk_50ms(void)
{

}

void vfnTsk_100ms(void)
{
  			
	u8100ms_Ctr++;
    u8100ms_Ctr2++;

	if (5 <= u8100ms_Ctr)
	{
		u8100ms_Ctr = 0;
		LED_Toggle( 0 );
	}
    if (10 <= u8100ms_Ctr2)
	{
		u8100ms_Ctr2 = 0;
	}
	// Uart_EnableInt(0, 2, 1);
	// uint8_t pTxBuffer[] = {"Hello World!!\n\r"};
	// Std_ReturnType ret = Uart_SendByte(0,164);
	// Std_ReturnType ret = Uart_SendBuffer(0,(uint8_t *)&pTxBuffer, sizeof(pTxBuffer));
	//printf("E_ %u\n\r", ret);
}

