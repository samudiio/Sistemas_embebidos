/* 
 * Uart Driver
 * Pracica #3 Basic Software Architecture
 * Uart_Cfg.h
 *
 *  Created on: Oct 2017
 *  Brief:      Interfaces provided to the user config module
 */
#ifndef UART_CFG
#define UART_CFG

#include <Uart_Types.h>

#define CFG_PHYCH_UART0 = 0
#define CFG_PHYCH_UART1 = 1
#define CFG_PHYCH_UART2 = 2
#define CFG_PHYCH_UART3 = 3
#define CFG_PHYCH_UART4 = 4

#define CFG_INT_DISABLED = 0
#define CFG_INT_RXRDY = 1
#define CFG_INT_TXRDY = 2
#define CFG_INT_OVR_ERROR = 32
#define CFG_INT_FRAME_ERROR = 64
#define CFG_INT_PAR_ERROR = 128
#define CFG_INT_TXEMPTY = 512
// Buscar Valores Reales

#define CNF_UART0 (0X00)
#define CNF_UART0 (0X01)
#define CNF_UART0 (0X02)
#define CNF_UART0 (0X03)

#define CNF_UART_TXISREN (0X01)
#define CNF_UART_RXISREN (0X02)

#define CNF_UART_MODE_LOCAL (0X00)
#define CNF_UART_MODE_REMOTE (0X01)
#define CNF_UART_MODE_NORMAL (0X01)

#include <Std_Types.h>

typedef struct{
    uint8_t ChannelId;
    uint8_t IsrEn;
    uint8_t Mode;
    uint8_t Parity;
    uint8_t Baudrate;
    CallbackFunctionsType *Callbacks;
}Uart_ChannnelType;

typedef struct{
    uint8_t UartNumberOfChannels;
    const Uart_ChannnelType *ChannelConfig;
    uint8_t ClkSrc;
}Uart_ConfigType;

typedef struct{
    void (* TxNotification)(void);
    void (* RxNotification)(void);
    void (*ErrorNotification)(UartErrorType*);
}CallbackFunctionsType;
#endif