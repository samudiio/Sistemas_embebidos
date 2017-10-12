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

#define CFG_INT_DISABLED        0
#define CFG_INT_RXRDY           1
#define CFG_INT_TXRDY           2
#define CFG_INT_OVR_ERROR       32
#define CFG_INT_FRAME_ERROR     64
#define CFG_INT_PAR_ERROR       128
#define CFG_INT_TXEMPTY         512

typedef enum
{
    UartCfg_PhyCh_0 = 0,
    UartCfg_PhyCh_1,
    UartCfg_PhyCh_2,
    UartCfg_PhyCh_3,
    UartCfg_PhyCh_4
}Uart_Ch_Type;

typedef uint32_t Uart_Interrupt_Type;

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

typedef enum
{
    UartCfg_Par_Even = 0,
    UartCfg_Par_Odd  = 1,
    UartCfg_Par_NO   = 4
}Uart_Parity_Type;

typedef uint32_t Uart_BaudRateType;

/*
 * Configuration parameters of the Uart callback notifications
 */
typedef struct
{
    void (*TxNotification)(void);
    void (*RxNotification)(void);
    void (*ErrorNotification)(uint8_t Error_Type);
}CallbackFunctionsType;

/*
 * Channel-specific configuration parameters
 */
typedef struct
{
    Uart_Ch_Type            ChannelId;            /*Physical Uart channel*/
    Uart_Interrupt_Type     InterruptEnable;
    Uart_ChMode_Type        TestMode;
    Uart_BrSrcCk_Type       BrSourceClk;
    Uart_Parity_Type        Parity;
    Uart_BaudRateType       BaudRate;
    CallbackFunctionsType   CallbackFunctions;
}Uart_ChannelConfigType;

/*
 * Driver-specific configuration parameters
 * Configuration of the UART (Uart driver) module
 */
typedef struct
{
    uint8_t UartNoOfChannels;
    const Uart_ChannelConfigType *PtrChannelConfig;
}Uart_ConfigType;


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


extern const Uart_ConfigType Uart_Config[];

#endif /* UART_CFG_H */
