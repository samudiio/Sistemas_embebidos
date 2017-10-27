#ifndef _UART_
#define _UART_

#include <Uart_Cfg.h>
#include <Uart_Types.h>


/*-- Includes ----------------------------------------------------------------*/
extern void Uart_Init(const UartConfigType*);
extern Std_ReturnType Uart_SetBaudrate(uint8_t, uint32_t);
extern void Uart_SetTxEnable(uint8_t, uint32_t);
extern void Uart_SetRxEnable(uint8_t, uint32_t); 
extern Std_ReturnType Uart_SendByte(uint8_t, uint8_t);
extern Std_ReturnType Uart_SendBuffer(uint8_t, uint8_t*, uint16_t);
extern void Uart_GetByte(uint8_t, uint8_t*); 
extern void Uart_EnableInt(uint8_t, uint32_t, uint8_t);
extern void Uart_GetStatus(uint8_t, uint32_t*);


uint32_t UART_IsTxReady(uint8_t Channel);
uint32_t UART_IsRxReady(uint8_t Channel);
        



#endif 