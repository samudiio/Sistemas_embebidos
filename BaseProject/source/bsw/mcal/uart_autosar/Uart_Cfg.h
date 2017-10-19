#ifndef _UART_CFG_
#define _UART_CFG_
/*-- Includes ----------------------------------------------------------------*/
#include "Std_Types.h"


#define CFG_PHYCH_UART0 (0X00)
#define CFG_PHYCH_UART1 (0X01)
#define CFG_PHYCH_UART2 (0X02)
#define CFG_PHYCH_UART3 (0X03)
#define CFG_PHYCH_UART4 (0X04)

#define CFG_INT_DISABLED  	 0
#define CFG_INT_RXRDY  		   1
#define CFG_INT_TXRDY  		   2
#define CFG_INT_OVR_ERROR  	 32
#define CFG_INT_FRAME_ERROR  64
#define CFG_INT_PAR_ERROR  	 128
#define CFG_INT_TXEMPTY 	   512

#define CFG_CLKSRC_PERIPHERAL   0
#define CFG_CLKSRC_PROGRAMMABLE 1

#define CFG_MODE_NORMAL         	  0
#define CFG_MODE_AUTOMATIC  	      1
#define CFG_MODE_LOCAL_LOOPBACK 	  2
#define CFG_MODE_REMOTE_LOOPBACK	  3

#define CFG_PARITY_EVEN		0
#define CFG_PARITY_ODD		1
#define CFG_PARITY_NONE		4

typedef struct
{
	void(*TxNotification)(void);
	void(*RxNotification)(void);
	void(*ErrorNotification)(uint8_t *UartErrorType);
}CallbackFunctionsType;

typedef struct
{
	uint8_t ChannelID;
	uint8_t IsrEn;
	uint8_t Mode;
	uint8_t Parity;
	uint32_t Baudrate;
	CallbackFunctionsType Callbacks;	
}UartChannelType;

typedef struct
{
	uint8_t UartNumberOfChannels;
	uint8_t ClkSrc;
	const UartChannelType *ChannelConfig;	
}UartConfigType;


extern const UartConfigType Uart_Config[];

/*
 * Brief: End of transmission notification
 */
void vfnTxNotification(void);

/*
 * Brief: Data reception notification
 */
void vfnRxNotification(void);

/*
 * Brief: Error notification
 */
void vfnErrorNotification(uint8_t Error_Type);




#endif 