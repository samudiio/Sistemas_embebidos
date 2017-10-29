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

#define UART_CNF_RXISREN        (0x1u << 0)
#define UART_CNF_TXISREN        (0x1u << 1)

#define UART_CFG_INT_DISABLED        0x00
#define UART_CFG_INT_RXRDY           0x01
#define UART_CFG_INT_TXRDY           0x02
#define UART_CFG_INT_OVR_ERROR       0x20
#define UART_CFG_INT_FRAME_ERROR     0x40
#define UART_CFG_INT_PAR_ERROR       0x80
#define UART_CFG_INT_TXEMPTY         0x200

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
    UART_ERROR_OVERRUN = 0,
    UART_ERROR_FRAMING = 1,
    UART_ERROR_PARITY = 2
}UartErrorType;

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
    Uart_Ch_Type                    ChannelId;            /*Physical Uart channel*/
    Uart_Interrupt_Type             InterruptEnable;
    Uart_ChMode_Type                TestMode;
    Uart_Parity_Type                Parity;
    Uart_BaudRateType               BaudRate;
    const CallbackFunctionsType     *CallbackFunctions;
}Uart_ChannelConfigType;

/*
 * Driver-specific configuration parameters
 * Configuration of the UART (Uart driver) module
 */
typedef struct
{
    uint8_t                         UartNoOfChannels;
    Uart_BrSrcCk_Type               BrSourceClk;
    const Uart_ChannelConfigType    *PtrChannelConfig;
}Uart_ConfigType;


/*
 * Brief: End of transmission notification
 */
extern void vfnUART_TxComplete(void);

/*
 * Brief: Data reception notification
 */
extern void vfnUART_RxComplete(void);

/*
 * Brief: Error notification
 */
extern void vfnErrorNotification(uint8_t Error_Type);


extern const Uart_ConfigType Uart_Config[];

#endif /* UART_CFG_H */
