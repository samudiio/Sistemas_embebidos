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
    Uart_EnableInt(0, 2, 0);
    Uart_EnableInt(0, 1, 1);
}

void FnRxNotification(void){
    uint8_t dta;
    Uart_GetByte(0, &dta);
    printf("Recibido: %c\n\r", dta);
    Uart_EnableInt(0, 1, 0);
    Uart_EnableInt(0, 2, 1);
}

void FnErrNotification(UartErrorType Error){
    printf("Error No. %u\n\r", Error);
}

// Configuracion
const Uart_ChannnelType UartChannelCfg[]={
    {
        CFG_PHYCH_UART4,
        //(CFG_INT_TXEMPTY | CFG_INT_TXRDY),
        (CFG_INT_RXRDY | CFG_INT_TXRDY),
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
    sizeof(UartChannelCfg)/sizeof(Uart_ChannnelType),
    UartChannelCfg,
    CNF_CLKSRC_PERIPHERAL
};





