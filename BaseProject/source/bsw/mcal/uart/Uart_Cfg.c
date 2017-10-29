/*
 * Uart_Cfg.c
 *
 *  Created on: Oct 5, 2017
 *  Brief:
 */

#include "Std_Types.h"
#include "Uart_Cfg.h"


 const CallbackFunctionsType UartCallbackFunctions[] =
{
  {
    vfnUART_TxComplete,
    vfnUART_RxComplete,
    vfnErrorNotification
  }
};

/*
 * Uart Channel Configuration
 */
const Uart_ChannelConfigType ChannelConfig[] =
{
    /*Logical Channel 0*/
    {
        UartCfg_PhyCh_4,
        (UART_CNF_TXISREN | UART_CNF_RXISREN),
        UartCfg_Mde_Normal,
        UartCfg_Par_NO,
        115200,
        &UartCallbackFunctions[0]
    },
    /*Logical Channel 1*/
    {
        UartCfg_PhyCh_0,
        UART_CFG_INT_DISABLED,
        UartCfg_Mde_Local_Loopback,
        UartCfg_Par_Even,
        19200,
        NULL
    }
};

/*
 * Uart Configuration
 */
const Uart_ConfigType Uart_Config[] =
{
    {
        sizeof(ChannelConfig)/sizeof(ChannelConfig[0]),
        UartCfg_Clk_Peripheral,
        &ChannelConfig[0]
    }
};

