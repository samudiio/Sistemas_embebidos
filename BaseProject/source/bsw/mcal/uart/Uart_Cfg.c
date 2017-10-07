/*
 * Uart_Cfg.c
 *
 *  Created on: Oct 5, 2017
 *  Brief:
 */

#include "Std_Types.h"
#include "Uart_Cfg.h"


/*
 * Uart Channel Configuration
 */
const Uart_ChannelConfigType ChannelConfig[] =
{
    {
        UartCfg_Ch0,
        UART_CFG_TXISREN,
        UartCfg_Clk_Peripheral,
        UartCfg_Mde_Remote_Loopback,
        19200,
        UartCfg_Par_Even,
        vfnTxNotification,
        vfnRxNotification
    }
};

/*
 * Uart Configuration
 */
const Uart_ConfigType Uart_Config[] =
{
    {
        sizeof(ChannelConfig)/sizeof(ChannelConfig[0]),
        &ChannelConfig[0]
    }
};


void vfnTxNotification(void)
{
    /*do something*/
}

void vfnRxNotification(void)
{
    /*do something*/
}

