/*
 * Uart_Cfg.h
 *
 *  Created on: Sep 30, 2017
 *  Brief:
 */

#ifndef UART_CFG_H
#define UART_CFG_H

/*-- Includes ----------------------------------------------------------------*/
#include "Std_Types.h"

#define UART_CFG_TXISREN        0x01
#define UART_CFG_RXISREN        0x02


typedef enum
{
    UartCfg_Ch0 = 0,
    UartCfg_Ch1,
    UartCfg_Ch2,
    UartCfg_Ch3,
    UartCfg_Ch4
}Uart_Ch_Type;

typedef uint8_t Uart_Interrupt_Type;

typedef enum
{
    UartCfg_Clk_Peripheral = 0,
    UartCfg_Clk_PCK
}Uart_BrSrcCk_Type;

typedef enum
{
    UartCfg_Mde_Normal = 0,
    UartCfg_Mde_Automatic_Echo,
    UartCfg_Mde_Local_Loopback,
    UartCfg_Mde_Remote_Loopback
}Uart_ChMode_Type;

typedef uint16_t Uart_BaudRateType;

typedef enum
{
    UartCfg_Par_Even = 0,
    UartCfg_Par_Odd
}Uart_Parity_Type;

typedef void (*TxNotification)(void);
typedef void (*RxNotification)(void);

/*
 * Channel-specific configuration parameters
 */
typedef struct
{
    Uart_Ch_Type        ChannelId;            /*Physical Uart channel*/
    Uart_Interrupt_Type InterruptEnable;
    Uart_BrSrcCk_Type   SourceClk;
    Uart_ChMode_Type    TestMode;
    Uart_BaudRateType   BaudRate;
    Uart_Parity_Type    Parity;
    TxNotification      TxNtfFcnPtr;
    RxNotification      RxNtfFcnPtr;
    void (*ErrorNotification)(uint8_t Error_Type);
}Uart_ChannelConfigType;

/*
 * Driver-specific configuration parameters
 */
typedef struct
{
    uint8_t NoOfChannels;
    const Uart_ChannelConfigType *PtrChannelConfig;
}Uart_ConfigType;


void vfnTxNotification(void);

void vfnRxNotification(void);



#endif /* UART_CFG_H */
