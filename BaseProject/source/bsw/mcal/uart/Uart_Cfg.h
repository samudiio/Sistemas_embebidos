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
#include <Std_Types.h>

#define CFG_PHYCH_UART0 0
#define CFG_PHYCH_UART1 1
#define CFG_PHYCH_UART2 2
#define CFG_PHYCH_UART3 3
#define CFG_PHYCH_UART4 4

#define CFG_INT_DISABLED 0
#define CFG_INT_RXRDY 1
#define CFG_INT_TXRDY 2
#define CFG_INT_OVR_ERROR 32
#define CFG_INT_FRAME_ERROR 64
#define CFG_INT_PAR_ERROR 128
#define CFG_INT_TXEMPTY 512

#define CNF_UART_TXISREN (0x1u << 0)
#define CNF_UART_RXISREN (0x1u << 1)

#define CNF_UART_MODE_NORMAL (0x0u << 14)
#define CNF_UART_MODE_LOOPBACK  (0x2u << 14)

#define CNF_CLKSRC_PERIPHERAL (0x0u << 12)
#define CNF_CLKSRC_PROGRAMMABLE (0x1u << 12)

#define CNF_PARITY_EVEN (0x0u << 9)
#define CNF_PARITY_ODD  (0x1u << 9)

typedef struct{
    void (* TxNotification)(void);
    void (* RxNotification)(void);
    void (*ErrorNotification)(UartErrorType*);
}CallbackFunctionsType;

typedef struct{
    uint8_t ChannelId;
    uint32_t IsrEn;
    uint8_t Mode;
    uint8_t Parity;
    uint32_t Baudrate;
    CallbackFunctionsType Callbacks;
}Uart_ChannnelType;

typedef struct{
    uint8_t UartNumberOfChannels;
    const Uart_ChannnelType *ChannelConfig;
    uint8_t ClkSrc;
}Uart_ConfigType;

extern const Uart_ConfigType UART_Config;
#endif