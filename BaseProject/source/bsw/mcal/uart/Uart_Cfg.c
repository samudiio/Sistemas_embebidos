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
        UartCfg_PhyCh_0,
        UART_CFG_TXISREN,
        UartCfg_Mde_Remote_Loopback,
        UartCfg_Par_Even,
        19200,
        {
            vfnTxNotification,
            vfnRxNotification,
            vfnErrorNotification
        }
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

/*
 * Brief: End of transmission notification
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void vfnTxNotification(void)
{
    /*do something*/
}

/*
 * Brief: Data reception notification
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void vfnRxNotification(void)
{
    /*do something*/
}

/*
 * Brief: Error notification
 */
/*
 * Brief: Error notification
 * @Param in:
 *  None
 * @Param out:
 *  UartErrorType Error - Uart Error during transmission/reception
 * @Return type
 *  void
 */
void vfnErrorNotification(uint8_t Error_Type)
{
    /*do something*/
}
