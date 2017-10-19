
#include <Uart_Cfg.h>

void TxNotification(void){
  printf( "Callback TxNotification\n\r" );
  
}
void RxNotification(void){
  printf( "Callback RxNotification\n\r" );
  
}
void ErrorNotification(uint8_t *UartErrorType){
  printf( "Callback ErrorNotification\n\r" );
}


const UartChannelType UARTChannelCfg[] = 
{
	{
		CFG_PHYCH_UART4,
		(CFG_INT_RXRDY | CFG_INT_TXRDY),
		CFG_MODE_NORMAL,
		CFG_PARITY_NONE,
		115200,
		{TxNotification,NULL,NULL}		
	},
	{
		CFG_PHYCH_UART0,
		CFG_INT_RXRDY,
		CFG_MODE_NORMAL,
		CFG_PARITY_NONE,
		115200,
		{NULL,NULL,NULL}	
	}	
};

//Falta Declarar UartConfigType y que contenga al  de arriba UARTChannelCfg[]

const UartConfigType Uart_Config[] =
{
   sizeof(UARTChannelCfg)/sizeof(UARTChannelCfg[0]),
   CFG_CLKSRC_PERIPHERAL,
   &UARTChannelCfg[0]
   
};
