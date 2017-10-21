
#include <Uart_Cfg.h>

void TxNotification(void){
  printf( "End of transmission notification\n\r" );
  
}
void RxNotification(void){
  printf( "Data reception notification\n\r" );
  
}
void ErrorNotification(uint8_t *UartErrorType){
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
		{TxNotification,NULL,NULL}		
	},
	{
		CFG_PHYCH_UART3,
		CFG_INT_RXRDY,
		CFG_MODE_NORMAL,
		CFG_PARITY_NONE,
		9600,
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
