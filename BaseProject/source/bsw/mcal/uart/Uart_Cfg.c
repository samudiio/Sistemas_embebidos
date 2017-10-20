/* 
Uart Driver
Pracica #3 Basic Software Architecture
Configuration of the UART (Uart driver) module
 */
#include <Uart_Cfg.h>
#include <uart.h>
#include <stdio.h>

void FnTxNotification(void){
    printf("Enviado \n\r");
}

void FnRxNotification(void){

}

void FnErrNotification(UartErrorType* Error){

}

// Configuracion
const Uart_ChannnelType UartChannelCfg[]={
    {
        CFG_PHYCH_UART4,
        //(CFG_INT_TXEMPTY | CFG_INT_TXRDY),
        (CFG_INT_TXRDY),
        (CNF_UART_MODE_NORMAL),
        CNF_PARITY_NO,
        115200,
        {
            FnTxNotification,
            FnRxNotification,
            FnErrNotification
        }
    }
};

const Uart_ConfigType UART_Config = {
    1,
    UartChannelCfg,
    CNF_CLKSRC_PERIPHERAL
};





