#ifndef _UART_TYPES_
#define _UART_TYPES_

/*-- Includes ----------------------------------------------------------------*/
//#include <typedefs.h>

#include "Std_Types.h"


#define UART_MASK_RXRDY  1
#define UART_MASK_TXRDY  2
#define UART_MASK_OVRE  32
#define UART_MASK_FRAME 64
#define UART_MASK_PARE  128
#define UART_MASK_TXEMPTY  512

typedef struct 
{
  uint8_t RxBusy;
  uint8_t TxBusy;
}UartStatusType;





#endif 