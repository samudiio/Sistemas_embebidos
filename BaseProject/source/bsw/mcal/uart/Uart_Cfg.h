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


// Buscar Valores Reales

#define CNF_UART0 (0X00)
#define CNF_UART0 (0X01)
#define CNF_UART0 (0X02)
#define CNF_UART0 (0X03)

#define CNF_UART_TXISREN (0X01)
#define CNF_UART_RXISREN (0X02)

#define CNF_UART_MODE_LOCAL (0X00)
#define CNF_UART_MODE_LOCAL (0X01)
#define CNF_UART_MODE_NORMAL (0X01)

#include <Std_Types.h>

typedef struct{
    uint8_t Channel;
    uint8_t InterrupEnable;
    uint8_t Mode;
    uint8_t Baudrate;
    uint8_t Parity;
    void (* TXNotification)(void);
    void (* RXNotification)(void);
}Uart_ChannnelType;

typedef struct{
    uint8_t NoOfChannels;
    const Uart_ChannnelType *ChannelConfig;
}Uart_ConfigType;


#endif