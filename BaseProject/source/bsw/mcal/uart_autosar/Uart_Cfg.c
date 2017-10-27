
#include <Uart_Cfg.h>
#include <stdio.h>
#include <serial_ctrl.h>



void TxNotification(void){
  vfnSerialCtrl_SendBuffer();
  printf( "End of transmission notification\n\r" );
  
}
void RxNotification(void){
  printf( "   Data reception notification\n\r" );  
  
}

//uint8_t *UartErrorType
void ErrorNotification(void){
  printf( "Error notification\n\r" );
}

const UartChannelType UARTChannelCfg[] = 
{
	{
		CFG_PHYCH_UART4,
		(CFG_INT_RXRDY | CFG_INT_TXRDY),
		CFG_MODE_NORMAL,
		CFG_PARITY_NONE,
		115200,
		{&TxNotification,&RxNotification,&ErrorNotification}		
	},
	{
		CFG_PHYCH_UART3,
		CFG_INT_RXRDY,
		CFG_MODE_NORMAL,
		CFG_PARITY_NONE,
		115200,
		{TxNotification,RxNotification,ErrorNotification}	
	}	
};

//Falta Declarar UartConfigType y que contenga al  de arriba UARTChannelCfg[]

const UartConfigType Uart_Config[] =
{
   sizeof(UARTChannelCfg)/sizeof(UARTChannelCfg[0]),
   CFG_CLKSRC_PERIPHERAL,
   &UARTChannelCfg[0]
   
};
